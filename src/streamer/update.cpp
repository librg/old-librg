// Copyright ReGuider Team, 2016-2017
//
#include <enet/enet.h>

#include <librg/core.h>
#include <librg/entities.h>
#include <librg/network.h>
#include <librg/streamer.h>
#include <librg/events.h>
#include <librg/components/client.h>

using namespace librg;

/**
 * Regulated ticker, should be used
 * to send regular messages to all connected clients
 */
void streamer::update()
{
    /**
     * Entity packing and sending
     */
    entities->each<client_t>([](entity_t player, client_t& client) {
        // core::log("sending updates to uid: %d", player.id().index());
        // copy last to local last, alias next snapshot as last and clear it
        auto next_snapshot = &client.last_snapshot;
        auto last_snapshot =  client.last_snapshot;

        next_snapshot->clear();
        auto queue = streamer::query(player);

        uint16_t created_entities = 0;
        uint16_t updated_entities = queue.size();

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

                events::trigger(events::on_create, new events::event_create_t {
                    guid, streamable->type, entity, &for_create
                });
            }
            else {
                for_update.write((uint64_t) guid);
                for_update.write((uint8_t) streamable->type);
                for_update.write(transform->position);
                for_update.write(transform->rotation);
                for_update.write(transform->scale);

                events::trigger(events::on_update, new events::event_update_t {
                    guid, streamable->type, entity, &for_update
                });
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

            auto entity = entities->get(entityx::Entity::Id(pair.first));
            auto streamable = entity.component<streamable_t>();

            events::trigger(events::on_remove, new events::event_remove_t {
                pair.first, streamable->type, entity, &for_create
            });
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
