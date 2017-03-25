#ifndef librg_network_h
#define librg_network_h

#include <map>
#include <array>
#include <string>
#include <functional>

#include <BitStream.h>
#include <RakPeerInterface.h>

#include <librg/components/client.h>
#include <librg/entities.h>

namespace librg
{
    void network_initialize();
    void network_terminate();

    namespace network
    {
        const short int PACKET_LIMIT = 256;
        using handler_t = std::array<std::function<void(RakNet::Packet* packet)>, PACKET_LIMIT>;

        struct data_t
        {
            RakNet::RakPeerInterface* peer;
            RakNet::SocketDescriptor socket_descriptor;
        };

        /**
         * Start the server
         * @param port
         */
        void server(int port);

        /**
         * Start the client
         * @param ip
         * @param port
         */
        void client(std::string ip, int port);

        /**
         * Call an update for network
         * Calculates update packets for clients
         */
        void update();

        /**
         * Calls a recieve update for network
         * (recieves new data from clients)
         */
        void receive();

        extern data_t data;
        extern std::map<RakNet::RakNetGUID, entityx::Entity> clients;
        extern handler_t handlers;
    }
}

#endif // librg_network_h
