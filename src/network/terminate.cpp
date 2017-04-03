// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>

using namespace librg;

void librg::network_terminate()
{
    for (auto pair : network::clients) {
        pair.second.destroy();
        // network::clients.erase(packet->guid);
    }

    network::data.peer->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(network::data.peer);
}
