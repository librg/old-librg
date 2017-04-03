// Copyright ReGuider Team, 2016-2017
//
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

    if (id == GUEST_PACKET_ENUM) {
        bitstream_t stream(packet->data, packet->length, false);
        stream.IgnoreBytes(sizeof(RakNet::MessageID));
        
        stream.Read(id);
        network::userHandlers[id](&stream, packet);
    }
    else if (network::handlers[id]) {
        network::handlers[id](packet);
    }

    network::data.peer->DeallocatePacket(packet);
}
