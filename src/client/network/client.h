#pragma once

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>

#include "../../common/network/commands.h"
#include "../../common/network/input_state.h"

#include "../game/entity.h"

namespace client {
    class Client final {
      public:
        Client(EntityArray &entites);
        bool connect(const sf::IpAddress &address); // Creates a connection request and sends to the server and configures settings if a connection slot is allocated
        void disconnect(); // Creates a disconnect packet and sends it to the server

        void sendInput(Input input); // Sends key input
        void update(); // Checks for packet from server and uses switch for figure out what handler to use

        bool isConnected() const; // Returns if the client is connected to the server

        ClientId getClientId() const; // Returns the client ID
        u8 getMaxPlayers() const; // Returns the max amount of players allowed on the server

      private:
        struct PackagedCommand {
            sf::Packet packet;
            CommandToClient command;
        };

        bool sendToServer(sf::Packet &packet); // Sends a packet to the server and returns if it was successful
        bool getFromServer(PackagedCommand &package); // Checks if there is a packet ready to be recieved and then stores it in a package and returns true

        void handleWorldState(sf::Packet &packet); // Unpacks packet with worldstate data (position, rotations)
        void handlePlayerJoin(sf::Packet &packet); // Configures entity array to set new player ID to alive
        void handlePlayerLeave(sf::Packet &packet); // Configures entity array to set new player ID to dead

        sf::UdpSocket m_socket;
        sf::IpAddress m_serverIpAddress;
        Port m_serverPort;
        ClientId m_clientId;
        Input m_inputState = 0;
        bool m_isConnected = false;

        u8 m_serverMaxPlayers = 0;

        EntityArray &mp_entities;
    };
} // namespace client
