// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/network.h>
#include <librg/entities.h>
#include <librg/network/controllers.h>

using namespace librg;

network::host_t* network::host;
network::peer_t* network::peer;

std::unordered_map<network::peer_t*, entity_t> network::connected_peers;
std::array<network::callback_t, LIBRG_NETWORK_MESSAGES> network::message_handlers;

void librg::network_initialize()
{
    network::host = nullptr;
    network::peer = nullptr;

    if (enet_initialize() != 0) {
        core::error("an error occurred while initializing network.");
        return;
    }

    network::message_handlers[network::connection_init]         = network::connection_controller::init;
    network::message_handlers[network::connection_request]      = network::connection_controller::request;
    network::message_handlers[network::connection_refuse]       = network::connection_controller::refuse;
    network::message_handlers[network::connection_accept]       = network::connection_controller::accept;
    network::message_handlers[network::connection_disconnect]   = network::connection_controller::disconnect;
    network::message_handlers[network::entity_create]           = network::entity_controller::create;
    network::message_handlers[network::entity_update]           = network::entity_controller::update;
}

/**
 * Storage for handlers
 */
// network::handler_t network::handlers;

/**
 * Storage for user handlers
 */
// network::user_handler_t network::userHandlers;

/**
 * Storage for network data
 */
// network::data_t network::data;

/**
 * Storage for current clients
 */
// std::map<RakNet::RakNetGUID, entity_t> network::clients;

/**
* Storage for network configuration
*/
// uint16_t network::platformId;
// uint16_t network::protoVersion;
// uint16_t network::buildVersion;
// uint16_t network::tickRate;
