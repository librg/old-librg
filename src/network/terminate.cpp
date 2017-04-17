// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>

using namespace librg;

void librg::network_terminate()
{
    // for (auto pair : network::clients) {
    //     pair.second.destroy();
    //     // network::clients.erase(packet->guid);
    // }

    if (network::peer) {
        core::log("disconnecting from server");
        enet_peer_disconnect(network::peer, 0);
        enet_peer_reset(network::peer);
    }

    enet_deinitialize();
}
