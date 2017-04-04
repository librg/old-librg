// Copyright ReGuider Team, 2016-2017
//
#include <unordered_map>

#include <librg/network.h>
#include <librg/entities.h>
#include <librg/streamer.h>
#include <librg/core/shared.h>

using namespace librg;

/**
 * Regulated ticker, should be used
 * to send regular messages to all connected clients
 */
void librg::network::update()
{
    entities->each<client_t>([](Entity playerEntity, client_t& client) {
        // core::log("sending updates to uid: %d", playerEntity.id().index());
        // copy last to local last, alias next snapshot as last and clear it
        auto next_snapshot = &client.last_snapshot;
        auto last_snapshot =  client.last_snapshot;

        next_snapshot->clear();
        auto queue = streamer::query(playerEntity);

        RakNet::BitStream packet;

        packet.Write((RakNet::MessageID) network::ENTITY_SYNC_PACKET);
        packet.Write((uint16_t) queue.size());

        for (auto entity : queue) {
            uint64_t guid = entity.id().id();
            packet.Write((uint64_t) guid);

            auto streamable = entity.component<streamable_t>();
            auto transform  = entity.component<transform_t>();

            bool isNew = false;

            if (last_snapshot.erase(guid) == 0) {
                // entity create
                packet.Write((bool) true);

                isNew = true;
            }
            else {
                // entity update
                packet.Write((bool) false);
            }

            packet.Write((uint8_t) streamable->type);
            packet.Write(transform->position.value);
            packet.Write(transform->rotation.value);
            packet.Write(transform->scale.value);

            if (isNew && syncCallbacks[core::rgmode::mode_server]) {
                syncCallbacks[core::rgmode::mode_server](&packet, entity, streamable->type);
            }
            
            next_snapshot->insert(std::make_pair(guid, true));
        }

        packet.Write((uint16_t) last_snapshot.size());

        for (auto pair : last_snapshot) {
            // remove entity
            packet.Write((uint64_t) pair.first);
        }

        data.peer->Send(&packet, HIGH_PRIORITY, RELIABLE_ORDERED, 0, client.address, false);
    });

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
