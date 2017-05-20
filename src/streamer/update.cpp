// Copyright ReGuider Team, 2016-2017
//
#include <enet/enet.h>

#include <librg/core.h>
#include <librg/events.h>
#include <librg/entities.h>
#include <librg/network.h>
#include <librg/streamer.h>

#include <librg/components/client.h>
#include <librg/components/server_owned.h>
#include <librg/components/client_streamable.h>

using namespace librg;

/**
 * Regulated ticker, should be used
 * to send regular messages to all connected clients
 */
void streamer::update()
{
    if (core::is_client()) {
        auto data   = network::bitstream_t();
        auto amount = 0;

        data.write_uint16(network::client_streamer_update);
        data.write_uint16(0); // amount of entities to be sent (updates)

        entities->each<client_streamable_t>([&data, &amount](entity_t entity, client_streamable_t &client) {
            auto streamable     = entity.component<streamable_t>();
            auto server_owned   = entity.component<server_owned_t>();

            data.write_uint64(server_owned->guid);

            events::trigger(events::on_client_stream_entity, new events::event_bs_entity_t(
                &data, entity, server_owned->guid, streamable->type
            ));

            amount++;
        });

        data.write_at((uint16_t) amount, sizeof(uint16_t));

        for (auto pair : network::connected_peers) {
            enet_peer_send(pair.first, 1, enet_packet_create(data.raw(), data.raw_size(), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT));
        }

        return;
    }

    entities->each<client_t>([](entity_t player, client_t &client) {
        if (!client.active) return;

        // copy last to local last, alias next snapshot as last and clear it
        auto next_snapshot = &client.last_snapshot;
        auto last_snapshot =  client.last_snapshot;

        next_snapshot->clear();
        auto queue = streamer::query(player);

        uint16_t created_entities = 0;
        uint16_t updated_entities = (uint16_t)queue.size();

        // create data and write inital stuff
        network::bitstream_t for_create;
        network::bitstream_t for_update;

        for_create.write((uint16_t) network::entity_create);
        for_create.write((uint16_t) created_entities);

        for_update.write((uint16_t) network::entity_update);
        for_update.write((uint16_t) updated_entities);

        // add entity creates and updates
        for (auto entity : queue) {
            uint64_t guid = entity.id().id();

            auto streamable = entity.component<streamable_t>();
            auto transform  = entity.component<transform_t>();

            if (last_snapshot.erase(guid) == 0) {
                created_entities++;
                updated_entities--;

                for_create.write((uint64_t) guid);
                for_create.write((uint8_t) streamable->type);
                for_create.write(transform->position);
                for_create.write(transform->rotation);
                for_create.write(transform->scale);

                events::trigger(events::on_create, new events::event_bs_entity_t(
                    &for_create, entity, guid, streamable->type
                ));
            }
            else {
                for_update.write((uint64_t) guid);
                for_update.write((uint8_t) streamable->type);
                for_update.write(transform->position);
                for_update.write(transform->rotation);
                for_update.write(transform->scale);

                events::trigger(events::on_update, new events::event_bs_entity_t(
                    &for_update, entity, guid, streamable->type
                ));
            }

            next_snapshot->insert(std::make_pair(guid, true));
        }

        for_create.write_at((uint16_t) created_entities, sizeof(uint16_t));
        for_update.write_at((uint16_t) updated_entities, sizeof(uint16_t));

        for_create.write((uint16_t) last_snapshot.size());

        // add entity removes
        for (auto pair : last_snapshot) {
            for_create.write((uint64_t) pair.first);

            // skip calling callback, if the entity is destroyed already.
            if (!entities->valid((entityx::Entity::Id)pair.first)) continue;

            auto entity = entities->get(entity_t::Id(pair.first));
            auto streamable = entity.component<streamable_t>();

            events::trigger(events::on_remove, new events::event_bs_entity_t(
                &for_create, entity, pair.first, streamable->type
            ));
        }

        enet_peer_send(client.peer, 0, enet_packet_create( for_create.raw(), for_create.raw_size(), ENET_PACKET_FLAG_RELIABLE ));
        enet_peer_send(client.peer, 1, enet_packet_create( for_update.raw(), for_update.raw_size(), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT ));
    });

    /**
     * Rebuilding entity tree
     * TODO(inlife): move to a separate thread and place
     */
    streamer::clear();

    entities->each<streamable_t>([](entity_t entity, streamable_t& streamable) {
        streamer::insert(entity);
    });
}
