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
    char my_host[16];

    while (enet_host_service(network::host, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                {
                    printf("a packet of length %u containing %s was received from %s on channel %u.\n",
                            (uint32_t)event.packet->dataLength,
                            event.packet->data,
                            event.peer->data,
                            event.channelID);

                    auto id = *(uint16_t*)(event.packet->data);

                    if (network::message_handlers[id]) {
                        network::message_handlers[id](event.peer, event.packet, event.channelID);
                    }
                    else {
                        core::error("network: unknown message: %d", id);
                    }

                    enet_packet_destroy(event.packet);
                }
                break;
            case ENET_EVENT_TYPE_CONNECT:
                network::message_handlers[network::connection_init](event.peer, nullptr, 0);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                enet_address_get_host_ip(&event.peer->address, my_host, 16);
                core::log("%s:%u disconnected.", my_host, event.peer->address.port);

                network::message_handlers[network::connection_disconnect](event.peer, nullptr, 0);
            case ENET_EVENT_TYPE_NONE: break;
        }
    }
}
