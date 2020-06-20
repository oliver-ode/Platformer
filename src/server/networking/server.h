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
        Server(int maxConnections); // Initializes sockets and sets up entity and client arrays/vectors

        void run(sf::Time timeout = sf::seconds(7.5)); // Main look that calls for recieving and sending packets

        bool isRunning() const; // Returns if the server itself is running

      private:
        struct PackagedCommand { // Structure that deals with all infomration about a certain packet of information
            sf::Packet packet; // Packet of information
            sf::IpAddress address; // Ip address of client
            CommandToServer command; // Command they want to execute - connect, disconnect or keystate
            Port port; // Port of the connection
        };

        int findEmptySlot(); // Loops through all of the connection slots and finds one which is free

        void recievePackets(); // Loops though all UDP packets and handles the corresponding commands - keyinput, connection and disconnection
        void update(float dt); // Does the math and transformations on the different key inputs
        void sendPackets(); // Loops through all entities and packages a "state" packet which stores information about all client IDs, positions and rotations and sends it to all connected clients

        bool sendToClient(ClientId id, sf::Packet &packet); // Sends a certain packet to a certain client ID
        void sendToAllClients(sf::Packet &packet); // Sends a certain packet to all clients
        bool getFromClient(PackagedCommand &package); // Checks if the socket has recieved any packets and stores the packet in package.command and returns true

        void handleIncomingConnection(const sf::IpAddress &address, Port port);

        void handleDisconnect(sf::Packet &packet); // Removes client associations with the server and sends a player leave packet to all clients
        void handleKeyInput(sf::Packet &packet); // Gets the key input and resultant mouse movement and stores it in memory

        sf::UdpSocket m_socket; // Main socket that deals with sending and recieving packets of data
        sf::Clock m_clock;
        sf::Clock m_exitClock;

        std::vector<ClientSession> m_clientSessions; // Information about the client session connection - ip address, port and keystate (forwards, back, left and/or right
        std::vector<ClientStatus> m_clientStatuses; // Stores Connected, Connecting or the base value Disconnected

        std::atomic<bool> m_isRunning = {false}; // Is the server running

        EntityArray m_entities; // Structure to store infomration about all of the entities in the game

        // std::queue<ClientEndpoint> m_pendingConnections;

        int m_maxConnections = 4; // Max connections
        int m_connections = 0; // Current amount of connections
        int m_aliveEntities = 0; // Current amount of alive entities
    };
} // namespace server
