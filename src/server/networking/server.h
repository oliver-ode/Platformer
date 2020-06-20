#pragma once

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/System/Clock.hpp>

#include <atomic>
#include <queue>
#include <vector>

#include "endpoint.h"
//#include "../game/entity.h"
#include <common/network/commands.h>

namespace server {
    class Server final {
      public:
        Server(int maxConnections);

        void run(sf::Time timeout = sf::seconds(7.5)); // Main look that calls for recieving and sending packets

        bool isRunning() const; // Returns if the server itself is running

      private:
        struct PackagedCommand {
            sf::Packet packet;
            sf::IpAddress address;
            CommandToServer command;
            Port port;
        };

        int findEmptySlot(); // Loops through all of the connection slots and finds one which is free

        void recievePackets();
        void update(float dt);
        void sendPackets();

        bool sendToClient(ClientId id, sf::Packet &packet); // Sends a certain packet to a certain client ID
        void sendToAllClients(sf::Packet &packet); // Sends a certain packet to all clients
        bool getFromClient(PackagedCommand &package); // Checks if the socket has recieved any packets and stores the packet in package.command and returns true

        void handleIncomingConnection(const sf::IpAddress &address, Port port);

        void handleDisconnect(sf::Packet &packet); // 
        void handleKeyInput(sf::Packet &packet);

        sf::UdpSocket m_socket;
        sf::Clock m_clock;
        sf::Clock m_exitClock;

        std::vector<ClientSession> m_clientSessions;
        std::vector<ClientStatus> m_clientStatuses;

        std::atomic<bool> m_isRunning = {false};

        EntityArray m_entities;

        // std::queue<ClientEndpoint> m_pendingConnections;

        int m_maxConnections = 4;
        int m_connections = 0;
        int m_aliveEntities = 0;
    };
} // namespace server
