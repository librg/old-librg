// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_network_server_connection_hpp
#define librg_network_server_connection_hpp

#include <librg/network.h>
#include <librg/streamer.h>
#include <librg/components/client.h>
#include <librg/components/streamable.h>
#include <librg/components/transform.h>
#include <librg/core/shared.h>
#include <librg/events.h>

namespace librg
{
    namespace network
    {
        /**
         * Client just send us first connection
         * init packet. Its the place where we should decide
         * was or was not he banned, and does he have access to our server
         */
        void server_new_incoming_connection(RakNet::Packet* packet);

        /**
         * Fires when user sends his username and serial
         * after he successfuly connected to raknet
         *
         * Packet structure
         * @param int MOSERVER_PROTOCOL_VERSION
         * @param int MOSERVER_BUILD_VERSION
         * @param string Client name
         * @param string Client serial
         */
        void server_connect(RakNet::Packet* packet);

        /**
         * On client disconnect
         */
        void server_disconnect(RakNet::Packet* packet);
    }
}

#endif // librg_network_server_connection_hpp
