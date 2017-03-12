#include <librg/network.h>

using namespace librg;

/**
 * Idle-ticker
 * Called with very high rate, should be used
 * only to handle some light, none-blocking ops
 */
void librg::network::receive()
{
    RakNet::Packet* packet = nullptr;

    if (!(packet = network::data.peer->Receive())) return;

    RakNet::MessageID id = packet->data[0];

    if (network::handlers[id]) {
        network::handlers[id](packet);
    }

    network::data.peer->DeallocatePacket(packet);
}
