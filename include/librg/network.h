#ifndef network_h
#define network_h

#include <map>
#include <string>
#include <array>

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
            RakNet::SystemAddress address;
            std::string nickname;
            std::string serial;
        };

        struct data_t
        {
            RakNet::RakPeerInterface* peer;
            RakNet::SocketDescriptor socket_descriptor;
        };

        void server(uint port);
        void client(std::string ip, uint port);

        void update();
        void receive();

        extern data_t data;
        extern std::map<RakNet::RakNetGUID, client_t> clients;
        extern handler_t handlers;
    }
}

#endif // network_h
