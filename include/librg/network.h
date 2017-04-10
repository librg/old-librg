// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_network_h
#define librg_network_h

#include <BitStream.h>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>

#include <librg/core.h>
#include <librg/entities.h>
#include <librg/components/client.h>
#include <librg/network/http/client.h>

namespace librg
{
    void network_initialize();
    void network_terminate();

    namespace network
    {
        constexpr int MAX_MESSAGES = 256;

        using bitstream_t          = RakNet::BitStream;
        using packet_t             = RakNet::Packet;
        using callback_t           = std::function<void(packet_t* packet)>;
        using user_callback_t      = std::function<void(bitstream_t* bitstream, packet_t* packet)>;
        using handler_t            = std::array<callback_t, MAX_MESSAGES>;
        using user_handler_t       = std::unordered_map<int, user_callback_t>;
        using message_t            = std::function<void(bitstream_t* message)>;
        using guid_t               = uint64_t;

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
            GUEST_PACKET_ENUM,
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
         * (server receives new data from clients)
         * (client receives new data from server)
         */
        void receive();

        /**
         * Send message from the client to server
         * or from server to all clients
         * @param messageid
         * @param message_t
         */
        void msg(int id, message_t callback);

        /**
        * Send message from the server to client
        * @param messageid
        * @param address
        * @param message_t
        */
        void msg(int id, RakNet::SystemAddress address, message_t callback);

        /**
        * Send message from the server to client
        * @param entity
        * @param messageid
        * @param message_t
        */
        void msg(int id, entity_t entity, message_t callback);

        /**
         * Register custom network event handler.
         * @param messageid
         * @param callback_t
         */
        void add(int messageid, user_callback_t callback);

        /**
        * Interpolate client data based on our current input values.
        * @param dt The time between 2 client ticks.
        */
        void interpolate(double dt);

        extern data_t data;
        extern std::map<RakNet::RakNetGUID, entity_t> clients;
        extern handler_t handlers;
        extern user_handler_t userHandlers;
    }
}

#endif // librg_network_h
