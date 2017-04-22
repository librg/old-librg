// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>

using namespace librg;

void network::poll()
{
    if (network::host == nullptr) {
        return;
    }

    ENetEvent event;

    while (enet_host_service(network::host, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                {
                    // core::log("a packet of length %u containing %s was received from %s on channel %u.\n",
                    //         (uint32_t)event.packet->dataLength,
                    //         event.packet->data,
                    //         event.peer->data,
                    //         event.channelID);

                    uint16_t id = 0;
                    auto data   = network::bitstream_t();

                    data.set_raw(event.packet->data);
                    data.read(id);

                    if (network::message_handlers[id]) {
                        network::message_handlers[id](event.peer, event.packet, &data);
                    }
                    else {
                        core::error("network: unknown message: %d", id);
                    }

                    enet_packet_destroy(event.packet);
                }
                break;
            case ENET_EVENT_TYPE_CONNECT:
                network::message_handlers[network::connection_init](event.peer, nullptr, nullptr);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                network::message_handlers[network::connection_disconnect](event.peer, nullptr, nullptr);
                break;
            case ENET_EVENT_TYPE_NONE: break;
        }
    }
}
