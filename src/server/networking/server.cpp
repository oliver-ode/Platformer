#include "server.h"

#include <SFML/Network/Packet.hpp>

#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <fstream>
#include <string>
#include <string.h>

namespace server {
    Server::Server(int maxConnections):m_clientSessions(maxConnections), m_clientStatuses(maxConnections){
        std::fill(m_clientStatuses.begin(), m_clientStatuses.end(),ClientStatus::Disconnected);

        m_socket.setBlocking(false);
        m_socket.bind(PORT);

        std::cout << "\n\nServer has started!" << std::endl;
        std::cout << "Listening for connections...\n" << std::endl;

        for (auto& entity : m_entities) {
            entity.alive = false;
        }
        loadMap();

        m_isRunning = true;
    }

    void Server::loadMap(){
        std::ifstream map_file("assets/tileset/map1.map");
        if (!map_file) {
            std::cout<<"Unable to open file"<<std::endl;
        }

        std::string line, c;
        int col, row = 0;
        while(getline(map_file, line)){
            col = 0;
            for(int i = 0; i < 27*2-1; i++){
                c = line[i];
                if(strcmp(c.c_str(), " ") != 0) {
                    m_map[row][col] = stoi(c);
                }
            }
        }
    }

    void Server::run(sf::Time timeout){
        sf::Clock dtClock;
        while (m_isRunning) {
            std::this_thread::sleep_for(std::chrono::milliseconds(33));

            recievePackets();
            update(dtClock.restart().asSeconds());
            sendPackets();

            if (m_connections == 0) {
                if (m_exitClock.getElapsedTime() > timeout) {
                    m_isRunning = false;
                }
            }
            else {
                m_exitClock.restart();
            }
        }
    }

    bool Server::isRunning() const{
        return m_isRunning;
    }

    int Server::findEmptySlot(){
        for (int i = 0; i < m_maxConnections; i++) {
            if (m_clientStatuses[i] == ClientStatus::Disconnected) {
                return i;
            }
        }
        return -1;
    }

    void Server::recievePackets(){
        PackagedCommand package;
        while (getFromClient(package)) {
            auto &packet = package.packet;
            switch (package.command) {
                case CommandToServer::KeyInput:
                    std::cout<<"Incoming key input packet"<<std::endl;
                    handleKeyInput(packet);
                    break;

                case CommandToServer::Connect:
                    handleIncomingConnection(package.address, package.port);
                    break;

                case CommandToServer::Disconnect:
                    handleDisconnect(packet);
                    break;
            }
        }
    }

    void Server::update(float dt){
        // Handle key input
        for (int i = 0; i < m_maxConnections; i++) {
            auto &input = m_clientSessions[i].keyState;
            auto &entity = m_entities[i];
            auto &position = entity.pos;
            auto &velocity = entity.velocity;

            auto isPressed = [input](KeyInput key) {
                return (input & key) == key;
            };

            if (isPressed(KeyInput::Right)) {
                velocity.x+=entity.movementSpeed;
            }
            else if (isPressed(KeyInput::Left)) {
                velocity.x-=entity.movementSpeed;
            }
            if (isPressed(KeyInput::Up) && colliding(entity, Hit::Bottom)) {
                // velocity.y-=entity.movementSpeed;
            }
            /* else if (isPressed(KeyInput::Down)) {
                velocity.y+=speed;
            } */
            position += velocity * dt;
            velocity *= 0.5f; // Friction - how fast the value deteriorates
        }
    }

    void Server::sendPackets(){
        sf::Packet statePacket;
        statePacket<<CommandToClient::WorldState<<static_cast<u16>(m_entities.size());
        for (u16 entityId = 0; entityId < m_entities.size(); entityId++) {
            if (m_entities[entityId].alive) {
                auto &position = m_entities[entityId].pos;
                auto &state = m_entities[entityId].state;
                auto &tick = m_entities[entityId].animationTick;
                statePacket<<entityId<<position.x<<position.y<<state<<tick;
            }
        }
        sendToAllClients(statePacket);
    }

    void Server::handleKeyInput(sf::Packet &packet){
        ClientId client;

        packet >> client;
        packet >> m_clientSessions[client].keyState;
    }

    bool Server::sendToClient(ClientId id, sf::Packet &packet){
        if (m_clientStatuses[id] == ClientStatus::Connected) {
            return m_socket.send(packet, m_clientSessions[id].address,m_clientSessions[id].port) == sf::Socket::Done;
        }
        return false;
    }

    void Server::sendToAllClients(sf::Packet &packet){
        for (int i = 0; i < m_maxConnections; i++) {
            sendToClient(i, packet);
        }
    }

    bool Server::getFromClient(PackagedCommand &package){
        if (m_socket.receive(package.packet, package.address, package.port) ==sf::Socket::Done) {
            package.packet >> package.command;
            return true;
        }
        return false;
    }

    void Server::handleIncomingConnection(const sf::IpAddress &clientAddress,Port clientPort){
        std::cout << "Connection request got\n";

        auto sendRejection = [this](ConnectionResult result,const sf::IpAddress &address, Port port) {
            auto rejectPacket =createCommandPacket(CommandToClient::ConnectRequestResult);
            rejectPacket << result;
            m_socket.send(rejectPacket, address, port);
        };

        // This makes sure there are not any duplicated connections
        for (const auto &endpoint : m_clientSessions) {
            if (clientAddress.toInteger() == endpoint.address.toInteger() &&
                clientPort == endpoint.port) {
                return;
            }
        }

        if (m_connections < m_maxConnections) {
            auto slot = findEmptySlot();
            if (slot < 0) {
                sendRejection(ConnectionResult::GameFull, clientAddress, clientPort);
            }
            // Connection can be made
            sf::Packet responsePacket;
            responsePacket<<CommandToClient::ConnectRequestResult<<ConnectionResult::Success<<static_cast<ClientId>(slot)<<static_cast<u8>(m_maxConnections);

            m_clientStatuses[slot] = ClientStatus::Connected;
            m_clientSessions[slot].address = clientAddress;
            m_clientSessions[slot].port = clientPort;
            m_entities[slot].pos = {0, 0};
            m_entities[slot].alive = true;
            m_entities[slot].jumpHeight = 25.0f;
            m_entities[slot].movementSpeed = 1.0f;
            m_entities[slot].hitted = 0;
            m_entities[slot].animationTick = 0;
            m_entities[slot].state = 0;

            m_aliveEntities++;
            m_socket.send(responsePacket, clientAddress, clientPort);

            m_connections++;
            std::cout << "Client Connected slot: " << (int)slot << '\n';

            auto joinPack = createCommandPacket(CommandToClient::PlayerJoin);
            joinPack << static_cast<ClientId>(slot);
            sendToAllClients(joinPack);
        }
        else {
            sendRejection(ConnectionResult::GameFull, clientAddress,clientPort);
        }
        std::cout << std::endl;
    }

    void Server::handleDisconnect(sf::Packet &packet){
        ClientId client;
        packet >> client;
        m_clientStatuses[client] = ClientStatus::Disconnected;
        m_entities[client].alive = false;
        m_connections--;
        m_aliveEntities--;
        std::cout << "Client Disonnected slot: " << (int)client << '\n';
        std::cout << std::endl;

        auto joinPack = createCommandPacket(CommandToClient::PlayerLeave);
        joinPack << client;
        sendToAllClients(joinPack);
    }

} // namespace server
