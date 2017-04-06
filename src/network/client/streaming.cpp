// Copyright ReGuider Team, 2016-2017
//
#include <vectorial/vectorial.h>

#include <librg/core.h>
#include <librg/network.h>
#include <librg/streamer.h>
#include <librg/network/client/streaming.h>

void librg::network::client_streamer_entity_sync(RakNet::Packet* packet) {

    RakNet::BitStream data(packet->data, packet->length, false);
    data.IgnoreBytes(sizeof(RakNet::MessageID));

    uint16_t query_size = 0, remove_size = 0;
    data.Read(query_size);

    // core::log("amount of objects: %d", query_size);

    for (int i = 0; i < query_size; ++i) {
        uint64_t guid = 0;
        bool create = false;
        uint8_t type = 0;

        data.Read(guid);
        data.Read(create);
        data.Read(type);

        // entities
        // TODO: figure out a better way
        // to store client-side entity objects

        // transform_t transform;
        simd4f position, rotation, scale;
        data.Read(position);
        data.Read(rotation);
        data.Read(scale);

        if (create) {
            auto entity = entities->create();
            entity.assign<streamable_t>();
            auto transform = entity.assign<transform_t>();

            transform->position.value = position;
            transform->rotation.value = rotation;
            transform->scale.value = scale;

            if (syncCallbacks[core::rgmode::mode_client]) {
                syncCallbacks[core::rgmode::mode_client](&data, entity, type);
            }

            streamer_callbacks::client_cache.insert(std::make_pair(guid, entity));
            streamer_callbacks::trigger(streamer_callbacks::create, guid, type, entity, (void *)packet);
        }
        else {
            if (streamer_callbacks::client_cache.find(guid) != streamer_callbacks::client_cache.end()) {
                auto entity = streamer_callbacks::client_cache[guid];
                auto transform = entity.component<transform_t>();

                transform->position.value = position;
                transform->rotation.value = rotation;
                transform->scale.value = scale;

                streamer_callbacks::trigger(streamer_callbacks::update, guid, type, entity, (void *)packet);
            }
            else {
                core::log("unexpected entity %lld on update", guid);
            }
        }
    }

    data.Read(remove_size);

    for (int i = 0; i < remove_size; ++i) {
        uint64_t guid = 0;
        data.Read(guid);

        if (streamer_callbacks::client_cache.find(guid) != streamer_callbacks::client_cache.end()) {
            auto entity = streamer_callbacks::client_cache[guid];
            // entity.component
            streamer_callbacks::trigger(streamer_callbacks::remove, guid, 0, entity, (void *)packet);
            streamer_callbacks::client_cache.erase(guid);
            entity.destroy();
        }
        else {
            core::log("unexpected entity %lld on remove", guid);
        }
    }

    return;
}
