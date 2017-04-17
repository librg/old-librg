// Copyright ReGuider Team, 2016-2017
//

#include <librg/core.h>
#include <librg/network.h>
#include <librg/callbacks.h>
#include <librg/streamer.h>
#include <librg/network/client/streaming.h>
#include <librg/components/interpolable.h>

// void librg::network::client_streamer_entity_sync(network::packet_t* packet) {

//     network::bitstream_t data(packet->data, packet->length, false);
//     data.IgnoreBytes(sizeof(RakNet::MessageID));

//     uint16_t query_size = 0, remove_size = 0;
//     data.Read(query_size);

//     // core::log("amount of objects: %d", query_size);

//     for (int i = 0; i < query_size; ++i) {
//         uint64_t guid = 0;
//         bool create = false;
//         uint8_t type = 0;

//         data.Read(guid);
//         data.Read(create);
//         data.Read(type);

//         // entities
//         // TODO: figure out a better way
//         // to store client-side entity objects

//         // transform_t transform;
//         hmm_vec3 position, rotation, scale;
//         data.Read(position);
//         data.Read(rotation);
//         data.Read(scale);

//         if (create) {
//             auto entity = entities->create();
//             auto streamable = entity.assign<streamable_t>();
//             streamable->type = type;
//             auto transform = entity.assign<transform_t>();

//             transform->position = position;
//             transform->rotation = rotation;
//             transform->scale    = scale;

//             streamer::entity_pool.insert(std::make_pair(guid, entity));

//             // trigger create or update callbacks for the client
//             callbacks::evt_create_t event = { guid, type, entity, &data };
//             callbacks::trigger(callbacks::create, (callbacks::evt_t*) &event);
//         }
//         else {
//             if (streamer::entity_pool.find(guid) == streamer::entity_pool.end()) {
//                 core::error("unexpected entity %lld on update", guid);
//                 continue;
//             }

//             auto entity = streamer::entity_pool[guid];
//             auto transform = entity.component<transform_t>();
//             auto interpolable = entity.component<interpolable_t>();

//             if (interpolable) {
//                 interpolable->lastTransform = transform_t(transform->position, transform->rotation, transform->scale);
//                 interpolable->targetTransform = transform_t(position, rotation, scale);
//                 interpolable->time = 0.0;
//             }

//             transform->position = position;
//             transform->rotation = rotation;
//             transform->scale = scale;

//             // trigger create or update callbacks for the client
//             callbacks::evt_update_t event = { guid, type, entity, &data };
//             callbacks::trigger(callbacks::update, (callbacks::evt_t*) &event);
//         }
//     }

//     data.Read(remove_size);

//     for (int i = 0; i < remove_size; ++i) {
//         uint64_t guid = 0;
//         data.Read(guid);

//         if (streamer::entity_pool.find(guid) != streamer::entity_pool.end()) {
//             auto entity = streamer::entity_pool[guid];
//             auto streamable = entity.component<streamable_t>();

//             // trigger remove callback
//             callbacks::evt_remove_t event = { guid, streamable->type, entity, &data };
//             callbacks::trigger(callbacks::remove, (callbacks::evt_t*) &event);

//             streamer::entity_pool.erase(guid);
//             entity.destroy();
//         }
//         else {
//             core::log("unexpected entity %lld on remove", guid);
//         }

//     }

//     return;
// }
