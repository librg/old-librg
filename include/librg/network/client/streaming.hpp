#ifndef librg_network_client_streaming_hpp
#define librg_network_client_streaming_hpp

#include <librg/network.h>
#include <librg/core/shared.h>

namespace librg
{
    namespace network
    {
        static inline void client_streamer_entity_sync(RakNet::Packet* packet) {
            core::log("received sync packet");

            RakNet::BitStream data(packet->data, packet->length, false);
            data.IgnoreBytes(sizeof(RakNet::MessageID));

            uint16_t query_size = 0, remove_size = 0;
            data.Read(query_size);

            core::log("amount of objects: %d", query_size);

            for (int i = 0; i < query_size; ++i) {
                uint64_t guid = 0;
                uint8_t type  = 0;
                bool create   = false;

                data.Read(guid);
                data.Read(create);
                data.Read(type);

                // entities
                // TODO: figure out a better way
                // to store client-side entity objects

                if (create) {
                    core::log("creating entity");
                }
                else {
                    core::log("updating entity");
                }
            }

            data.Read(remove_size);

            core::log("amount of objects to remove: %d", query_size);

            for (int i = 0; i < query_size; ++i) {
                core::log("removing entity");
            }

            return;
        }
    }
}

#endif // librg_network_client_streaming_hpp
