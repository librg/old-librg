// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>

using namespace librg;

/**
 * Idle-ticker
 * Called with very high rate, should be used
 * only to handle some light, none-blocking ops
 */
void librg::network::poll()
{
    if (network::host == nullptr) {
        return;
    }

    ENetEvent event;

    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service(network::host, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                printf("A packet of length %u containing %s was received from %s on channel %u.\n",
                        (uint32_t)event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);

                break;
            case ENET_EVENT_TYPE_CONNECT:
                printf("A new client connected from %x:%u.\n", event.peer -> address.host, event.peer -> address.port);
                /* Store any relevant client information here. */
                // event.peer->data = "Client information";
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%s disconnected.\n", event.peer -> data);
                /* Reset the peer's client information. */
                // event.peer->data = NULL;
            case ENET_EVENT_TYPE_NONE: break;
        }
    }
    // packet_t* packet = nullptr;

    // while ((packet = network::data.peer->Receive())) {
    //     RakNet::MessageID id = packet->data[0];

    //     if (id == GUEST_PACKET_ENUM) {
    //         bitstream_t stream(packet->data, packet->length, false);
    //         stream.IgnoreBytes(sizeof(RakNet::MessageID));

    //         stream.Read(id);
    //         if (network::userHandlers[id]) {
    //             network::userHandlers[id](&stream, packet);
    //         }
    //         else {
    //             core::error("Unknown message: %d", id);
    //         }
    //     }
    //     else if (network::handlers[id]) {
    //         network::handlers[id](packet);
    //     }

    //     network::data.peer->DeallocatePacket(packet);
    // }
}
