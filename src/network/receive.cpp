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
    packet_t* packet = nullptr;

    while ((packet = network::data.peer->Receive())) {
        RakNet::MessageID id = packet->data[0];

        if (id == GUEST_PACKET_ENUM) {
            bitstream_t stream(packet->data, packet->length, false);
            stream.IgnoreBytes(sizeof(RakNet::MessageID));

            stream.Read(id);
            if (network::userHandlers[id]) {
                network::userHandlers[id](&stream, packet);
            }
            else {
                core::error("Unknown message: %d", id);
            }
        }
        else if (network::handlers[id]) {
            network::handlers[id](packet);
        }

        network::data.peer->DeallocatePacket(packet);
    }
}
