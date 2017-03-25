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

            uint16_t query_size = 0;
            data.Read(query_size);

            core::log("amount of objects: %d", query_size);

            /**
             * This data-packet is used to validate
             * game mod compability, and add client to server list
             *
             * Data template
             * @param int NETWORK_PLATFORM_ID
             * @param int NETWORK_PROTOCOL_VERSION
             * @param int NETWORK_BUILD_VERSION
             * @param string Client Name
             */
            // RakNet::BitStream data;
            // data.Write((RakNet::MessageID)MessageID::CONNECTION_INIT);
            // data.Write(NETWORK_PLATFORM_ID);
            // data.Write(NETWORK_PROTOCOL_VERSION);
            // data.Write(NETWORK_BUILD_VERSION);
            // data.Write("Test Player");
            // data.Write("4555ASDASD4555ASDASD4555");
            // network::data.peer->Send(&data, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
        }
    }
}

#endif // librg_network_client_streaming_hpp
