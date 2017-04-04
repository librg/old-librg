// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_network_client_connection_hpp
#define librg_network_client_connection_hpp

#include <librg/network.h>
#include <librg/core/shared.h>

namespace librg
{
    namespace network
    {
        void client_remote_disconnect(RakNet::Packet* packet);

        void client_remote_connectionlost(RakNet::Packet* packet);

        void client_remote_newincoming(RakNet::Packet* packet);

        void client_new_incoming_connection(RakNet::Packet* packet);

        void client_no_free_incoming_connections(RakNet::Packet* packet);

        void client_disconnect_notification(RakNet::Packet* packet);

        void client_connection_lost(RakNet::Packet* packet);

        void client_connection_request_accepted(RakNet::Packet* packet);

        void client_connection_success(RakNet::Packet* packet);
    }
}

#endif // librg_network_client_connection_hpp
