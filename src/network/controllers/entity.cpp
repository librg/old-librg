// Copyright ReGuider Team, 2016-2017
//

#include <librg/core.h>
#include <librg/streamer.h>
#include <librg/events.h>
#include <librg/network.h>
#include <librg/network/controllers.h>
#include <librg/components/interpolable.h>

using namespace librg;
using namespace librg::network;

void entity_controller::create(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    uint16_t query_size = 0;
    data->read(query_size);

    for (int i = 0; i < query_size; ++i) {
        uint64_t guid = 0;
        uint8_t type  = 0;

        data->read(guid);
        data->read(type);

        // transform_t transform;
        hmm_vec3 position, scale;
        hmm_vec4 rotation;

        data->read(position);
        data->read(rotation);
        data->read(scale);

        auto entity         = entities->create();
        auto streamable     = entity.assign<streamable_t>();
        auto transform      = entity.assign<transform_t>();

        streamable->type    = type;
        transform->position = position;
        transform->rotation = rotation;
        transform->scale    = scale;

        streamer::entity_pool.insert(std::make_pair(guid, entity));

        events::trigger(events::on_create, new events::event_create_t {
            guid, type, entity, data
        });
    }

    uint16_t remove_size = 0;
    data->read(remove_size);

    for (int i = 0; i < remove_size; ++i) {
        uint64_t guid = 0;
        data->read(guid);

        if (streamer::entity_pool.find(guid) != streamer::entity_pool.end()) {
            auto entity     = streamer::entity_pool[guid];
            auto streamable = entity.component<streamable_t>();

            events::trigger(events::on_remove, new events::event_remove_t {
                guid, streamable->type, entity, data
            });

            streamer::entity_pool.erase(guid);
            entity.destroy();
        }
        else {
            core::log("unexpected entity %lld on remove", guid);
        }

    }
}

void entity_controller::update(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    uint16_t query_size = 0;
    data->read(query_size);

    for (int i = 0; i < query_size; ++i) {
        uint64_t guid = 0;
        uint8_t type  = 0;

        data->read(guid);
        data->read(type);

        // transform_t transform;
        hmm_vec3 position, scale;
        hmm_vec4 rotation;

        data->read(position);
        data->read(rotation);
        data->read(scale);

        if (streamer::entity_pool.find(guid) == streamer::entity_pool.end()) {
            continue;
        }

        auto entity         = streamer::entity_pool[guid];
        auto transform      = entity.component<transform_t>();
        auto interpolable   = entity.component<interpolable_t>();

        if (interpolable) {
            interpolable->latest    = transform_t(transform->position, transform->rotation, transform->scale);
            interpolable->target    = transform_t(position, rotation, scale);
            interpolable->time      = 0.0;
        }

        transform->position = position;
        transform->rotation = rotation;
        transform->scale    = scale;

        events::trigger(events::on_update, new events::event_update_t {
            guid, type, entity, data
        });
    }

}
