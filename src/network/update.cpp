// Copyright ReGuider Team, 2016-2017
//
#include <unordered_map>

#include <librg/core.h>
#include <librg/entities.h>
#include <librg/network.h>
#include <librg/streamer.h>
#include <librg/callbacks.h>

using namespace librg;

/**
 * Regulated ticker, should be used
 * to send regular messages to all connected clients
 */
void librg::network::update()
{
    /**
     * Entity packing adn sending
     */
    entities->each<client_t>([](entity_t player, client_t& client) {
        // core::log("sending updates to uid: %d", player.id().index());
        // copy last to local last, alias next snapshot as last and clear it
        auto next_snapshot = &client.last_snapshot;
        auto last_snapshot =  client.last_snapshot;

        next_snapshot->clear();
        auto queue = streamer::query(player);

        // create data and write inital data
        network::bitstream_t data;

        data.Write((RakNet::MessageID) network::ENTITY_SYNC_PACKET);
        data.Write((uint16_t) queue.size());

        // add entity creates and updates
        for (auto entity : queue) {
            uint64_t guid = entity.id().id();
            data.Write((uint64_t) guid);

            auto streamable = entity.component<streamable_t>();
            auto transform  = entity.component<transform_t>();

            bool creating_entity = (last_snapshot.erase(guid) == 0);

            data.Write((bool) creating_entity);
            data.Write((uint8_t) streamable->type);
            data.Write(transform->position.value);
            data.Write(transform->rotation.value);
            data.Write(transform->scale.value);

            // trigger create or update callbacks for the server
            callbacks::evt_create_t event = { guid, streamable->type, entity, &data };
            callbacks::trigger(creating_entity ? callbacks::create : callbacks::update, (callbacks::evt_t*) &event);

            next_snapshot->insert(std::make_pair(guid, true));
        }

        data.Write((uint16_t) last_snapshot.size());

        // add entity removes
        for (auto pair : last_snapshot) {
            data.Write((uint64_t) pair.first);

            auto entity = entities->get(entityx::Entity::Id(pair.first));
            auto streamable = entity.component<streamable_t>();

            callbacks::evt_remove_t event = { pair.first, streamable->type, entity, &data };
            callbacks::trigger(callbacks::remove, (callbacks::evt_t*) &event);
        }

        network::data.peer->Send(&data, HIGH_PRIORITY, RELIABLE_ORDERED, 0, client.address, false);
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
