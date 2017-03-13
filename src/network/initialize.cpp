#include <librg/network.h>
#include <librg/network/connection.hpp>
#include <librg/core/shared.h>

using namespace librg;

void librg::network_initialize()
{
    network::data.peer = RakNet::RakPeerInterface::GetInstance();

    // reset all registry to nulls
    for (int i = 0; i < network::PACKET_LIMIT; ++i) {
        network::handlers[i] = nullptr;
    }

    // connection stuff
    network::handlers[ID_NEW_INCOMING_CONNECTION]    = network::OnClientConnectAttempt;
    network::handlers[ID_CONNECTION_LOST]            = network::OnClientDisconnect;
    network::handlers[ID_DISCONNECTION_NOTIFICATION] = network::OnClientDisconnect;
    network::handlers[MessageID::CONNECTION_INIT]    = network::OnClientConnect;

    if (core::is_server()) {
        network::server(27010);
    }

    if (core::is_client()) {
        core::log("hello client");
    }
}

/**
 * Storage for handlers
 */
network::handler_t network::handlers;

/**
 * Storage for network data
 */
network::data_t network::data;

/**
 * Storage for current clients
 */
std::map<RakNet::RakNetGUID, network::client_t> network::clients;
