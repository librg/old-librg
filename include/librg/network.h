#ifndef network_h
#define network_h

#include <map>
#include <string>
#include <array>
#include <functional>

#include <RakPeerInterface.h>
#include <BitStream.h>

namespace librg
{
    void network_initialize();
    void network_terminate();

    namespace network
    {
        const short int PACKET_LIMIT = 256;
        using handler_t = std::array<std::function<void(RakNet::Packet* packet)>, PACKET_LIMIT>;

        struct client_t {
            client_t(RakNet::SystemAddress a, std::string n, std::string s) : address(a), nickname(n), serial(s) {}

            RakNet::SystemAddress address;
            std::string nickname;
            std::string serial;
        };

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
        extern std::map<RakNet::RakNetGUID, client_t> clients;
        extern handler_t handlers;
    }
}

#endif // network_h
