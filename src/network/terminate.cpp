#include <librg/network.h>

using namespace librg;

void librg::network_terminate()
{
    network::data.peer->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(network::data.peer);
}
