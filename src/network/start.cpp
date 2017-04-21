// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>

using namespace librg;

void network::start(config_t config)
{
    // setup address
    ENetAddress address = { .port = config.port };

    // start server or client
    if (core::is_server()) {
        core::log("starting server on port %d", address.port);

        address.host  = ENET_HOST_ANY;
        network::host = enet_host_create(&address, config.max_connections, LIBRG_NETWORK_CHANNELS, 0, 0);
    }
    else {
        network::host = enet_host_create(nullptr, 1, LIBRG_NETWORK_CHANNELS, 57600 / 8, 14400 / 8);
    }

    // verify host creation
    if (network::host == nullptr) {
        core::error("cannot create network host. this port may be already taken.");
        return;
    }

    // connect to server if client
    if (core::is_client()) {
        enet_address_set_host(&address, config.ip.c_str());

        core::log("connecting to server %x:%u", address.host, address.port);
        network::peer = enet_host_connect(network::host, &address, LIBRG_NETWORK_CHANNELS, 0);

        if (network::peer == nullptr) {
            core::error("cannot create peer to connect to the server");
        }
    }
}
