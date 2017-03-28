#ifndef librg_network_h
#define librg_network_h

#include <map>
#include <array>
#include <string>
#include <functional>

#include <BitStream.h>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>

#include <librg/components/client.h>
#include <librg/entities.h>

namespace librg
{
    void network_initialize();
    void network_terminate();

    namespace network
    {
        const short int PACKET_LIMIT = 256;

        using bitstream_t = RakNet::BitStream;
        using packet_t    = RakNet::Packet;
        using handler_t   = std::array<std::function<void(packet_t* packet)>, PACKET_LIMIT>;
        using message_t   = std::function<void(bitstream_t* message)>;

        struct data_t {
            RakNet::SystemAddress address;
            RakNet::RakPeerInterface* peer;
            RakNet::SocketDescriptor socket_descriptor;
        };

        enum messageid {
            CONNECTION_INIT = ID_USER_PACKET_ENUM + 1,
            CONNECTION_REFUSED,
            CONNECTION_ACCEPTED,
            CONNECTION_DISCONNECTED,
            ENTITY_SYNC_PACKET,
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

        /**
         * Send message from the client to server
         * or from server to all clients
         * @param messageid
         * @param message_t
         */
        void msg(messageid id, message_t callback);

        extern data_t data;
        extern std::map<RakNet::RakNetGUID, entityx::Entity> clients;
        extern handler_t handlers;
    }
}

#endif // librg_network_h
