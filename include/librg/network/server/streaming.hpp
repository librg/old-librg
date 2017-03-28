#ifndef librg_network_server_streaming_hpp
#define librg_network_server_streaming_hpp

namespace librg
{
    namespace network
    {
        /**
         * Client just send us first connection
         * init packet. Its the place where we should decide
         * was or was not he banned, and does he have access to our server
         */
        static inline void server_streamer_entity_sync(packet_t* packet)
        {
            bitstream_t data(packet->data, packet->length, false);
            data.IgnoreBytes(sizeof(RakNet::MessageID));

            float x, y;

            data.Read(x);
            data.Read(y);

            auto transform = network::clients[packet->guid].component<transform_t>();

            transform->position = vectorial::vec3f(x, y, transform->position.z());
        }
    }
}

#endif // librg_network_server_streaming_hpp
