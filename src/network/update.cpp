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
    entities->each<client_t>([](Entity playerEntity, client_t& client) {
        // copy last to local last, alias next snapshot as last and clear it
        auto next_snapshot = &client.last_snapshot;
        auto last_snapshot =  client.last_snapshot;

        next_snapshot->clear();
        auto queue = streamer::query(playerEntity);

        // create packet and write inital data
        network::bitstream_t packet;

        packet.Write((RakNet::MessageID) network::ENTITY_SYNC_PACKET);
        packet.Write((uint16_t) queue.size());

        // add entity creates and updates
        for (auto entity : queue) {
            uint64_t guid = entity.id().id();
            packet.Write((uint64_t) guid);

            auto streamable = entity.component<streamable_t>();
            auto transform  = entity.component<transform_t>();

            bool creating_entity = (last_snapshot.erase(guid) == 0);

            packet.Write((bool) creating_entity);
            packet.Write((uint8_t) streamable->type);
            packet.Write(transform->position.value);
            packet.Write(transform->rotation.value);
            packet.Write(transform->scale.value);

            if (creating_entity && core::is_server()) {
                callbacks::trigger(callbacks::sync, (callbacks::evt_t*) &callbacks::evt_sync_t(&packet, entity, streamable->type));
            }

            next_snapshot->insert(std::make_pair(guid, true));
        }

        packet.Write((uint16_t) last_snapshot.size());

        // add entity removes
        for (auto pair : last_snapshot) {
            packet.Write((uint64_t) pair.first);
        }

        data.peer->Send(&packet, HIGH_PRIORITY, RELIABLE_ORDERED, 0, client.address, false);
    });

    /**
     * Rebuilding entity tree
     * TODO(inlife): move to a separate thread and place
     */
    streamer::clear();

    entities->each<streamable_t>([](Entity entity, streamable_t& streamable) {
        streamer::insert(entity);
    });
}


// packet.Write((float) transform->position.x());
// packet.Write((float) transform->position.y());
// packet.Write((float) transform->position.z());
// packet.Write((float) transform->rotation.x());
// packet.Write((float) transform->rotation.y());
// packet.Write((float) transform->rotation.z());
// packet.Write((float) transform->scale.x());
// packet.Write((float) transform->scale.y());
// packet.Write((float) transform->scale.z());
