// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>

using namespace librg;

#define LIBRG_NETCHANNELS 2

void network::start(config_t config)
{
    // setup address
    ENetAddress address = { .port = config.port };

    // start server or client
    if (core::is_server()) {
        core::log("starting server on port %d", address.port);
        address.host = ENET_HOST_ANY;
        network::host = enet_host_create(&address, config.max_connections, LIBRG_NETCHANNELS, 0, 0);
    }
    else {
        network::host = enet_host_create(nullptr, 1, LIBRG_NETCHANNELS, 57600 / 8, 14400 / 8);
    }

    if (network::host == nullptr) {
        core::error("cannot create network host. this port may be already taken.");
        return;
    }

    if (core::is_client()) {
        enet_address_set_host(&address, config.ip.c_str());
        core::log("connecting to server %x:%u", address.host, address.port);

        network::peer = enet_host_connect(network::host, &address, LIBRG_NETCHANNELS, 0);

        if (network::peer == nullptr) {
            core::error("cannot create peer to connect to the server");
        }

        ENetEvent event;
        /* Wait up to 5 seconds for the connection attempt to succeed. */
        if (enet_host_service(network::host, &event, 5000) > 0 &&
            event.type == ENET_EVENT_TYPE_CONNECT)
        {
            puts ("Connection to some.server.net:1234 succeeded.");
        }
        else
        {
            /* Either the 5 seconds are up or a disconnect event was */
            /* received. Reset the peer in the event the 5 seconds   */
            /* had run out without any significant event.            */
            enet_peer_reset (network::peer);
            puts ("Connection to some.server.net:1234 failed.");
        }
    }
}
