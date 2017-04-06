// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/network.h>
#include <librg/network/server/connection.h>
#include <librg/network/client/connection.h>
#include <librg/network/client/streaming.h>

using namespace librg;

void librg::network_initialize()
{
    network::data.peer = RakNet::RakPeerInterface::GetInstance();

    if (core::is_server()) {
        network::handlers[ID_NEW_INCOMING_CONNECTION]           = network::server_new_incoming_connection;
        network::handlers[ID_CONNECTION_LOST]                   = network::server_disconnect;
        network::handlers[ID_DISCONNECTION_NOTIFICATION]        = network::server_disconnect;
        network::handlers[network::CONNECTION_INIT]             = network::server_connect;
    }

    if (core::is_client()) {
        network::handlers[ID_REMOTE_DISCONNECTION_NOTIFICATION] = network::client_remote_disconnect;
        network::handlers[ID_REMOTE_CONNECTION_LOST]            = network::client_remote_connectionlost;
        network::handlers[ID_REMOTE_NEW_INCOMING_CONNECTION]    = network::client_remote_newincoming;
        network::handlers[ID_NEW_INCOMING_CONNECTION]           = network::client_new_incoming_connection;
        network::handlers[ID_NO_FREE_INCOMING_CONNECTIONS]      = network::client_no_free_incoming_connections;
        network::handlers[ID_DISCONNECTION_NOTIFICATION]        = network::client_disconnect_notification;
        network::handlers[ID_CONNECTION_LOST]                   = network::client_connection_lost;
        network::handlers[ID_CONNECTION_REQUEST_ACCEPTED]       = network::client_connection_request_accepted;
        network::handlers[network::CONNECTION_ACCEPTED]         = network::client_connection_success;
        network::handlers[network::ENTITY_SYNC_PACKET]          = network::client_streamer_entity_sync;
    }
}

/**
 * Storage for handlers
 */
network::handler_t network::handlers;

/**
 * Storage for user handlers
 */
network::user_handler_t network::userHandlers;

/**
 * Storage for network data
 */
network::data_t network::data;

/**
 * Storage for current clients
 */
std::map<RakNet::RakNetGUID, entityx::Entity> network::clients;

/**
 * Storage for sync callbacks
 */
network::sync_callback_t network::syncCallbacks[2];
