// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/streamer.h>
#include <librg/events.h>
#include <librg/network.h>
#include <librg/network/controllers.h>
#include <librg/components/interpolable.h>
#include <librg/components/client_streamable.h>

using namespace librg;
using namespace librg::network;

void entity_controller::create(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    auto query_size = data->read_uint16();

    for (int i = 0; i < query_size; ++i) {
        auto guid = data->read_uint64();
        auto type  = data->read_uint8();

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

        events::trigger(events::on_create, new events::event_bs_entity_t(data, entity, guid, type));
    }

    uint16_t remove_size = 0;
    data->read(remove_size);

    for (int i = 0; i < remove_size; ++i) {
        auto guid = data->read_uint64();

        if (streamer::entity_pool.find(guid) != streamer::entity_pool.end()) {
            auto entity     = streamer::entity_pool[guid];
            auto streamable = entity.component<streamable_t>();

            events::trigger(events::on_remove, new events::event_bs_entity_t(data, entity, guid, streamable->type));

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
    auto query_size = data->read_uint16();

    for (int i = 0; i < query_size; ++i) {
        auto guid = data->read_uint64();
        auto type = data->read_uint8();

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

        events::trigger(events::on_update, new events::event_bs_entity_t(data, entity, guid, type));
    }
}

void entity_controller::client_streamer_add(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    auto guid = data->read_uint64();

    if (streamer::entity_pool.find(guid) == streamer::entity_pool.end()) {
        return;
    }

    auto entity = streamer::entity_pool[guid];

    if (!entity.has_component<client_streamable_t>()) {
        entity.assign<client_streamable_t>();
    }
}

void entity_controller::client_streamer_remove(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    auto guid = data->read_uint64();

    if (streamer::entity_pool.find(guid) == streamer::entity_pool.end()) {
        return;
    }

    auto entity = streamer::entity_pool[guid];

    if (entity.has_component<client_streamable_t>()) {
        entity.remove<client_streamable_t>();
    }
}
