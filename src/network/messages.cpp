// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>
#include <librg/streamer.h>

using namespace librg;

void network::set(uint16_t id, network::callback_t callback)
{
    if (network::message_handlers[id]) {
        core::error("warning: you are redefining network message with id: %d", id);
    }

    network::message_handlers[id] = callback;
}

void network::msg(uint16_t id, network::peer_t* peer, network::message_t callback)
{
    // create
    network::bitstream_t message;

    // write data
    message.write(id);
    if (callback) { callback(&message); }

    // send it!
    enet_peer_send(peer, 3, enet_packet_create(message.raw(), message.raw_size(), ENET_PACKET_FLAG_RELIABLE));
}

// void librg::network::msg(int id, network::message_t callback)
// {
//     network::bitstream_t message;

//     message.Write((RakNet::MessageID) GUEST_PACKET_ENUM);
//     message.Write((RakNet::MessageID) id); callback(&message);

//     network::data.peer->Send(&message, HIGH_PRIORITY, RELIABLE_ORDERED, 0, network::data.address, false);
// }

// void librg::network::msg(int id, RakNet::SystemAddress address, network::message_t callback)
// {
//     network::bitstream_t message;

//     message.Write((RakNet::MessageID) GUEST_PACKET_ENUM);
//     message.Write((RakNet::MessageID) id); callback(&message);

//     network::data.peer->Send(&message, HIGH_PRIORITY, RELIABLE_ORDERED, 0, address, false);
// }

// void librg::network::msg(int id, entity_t entity, network::message_t callback)
// {
//     network::bitstream_t message;

//     message.Write((RakNet::MessageID) GUEST_PACKET_ENUM);
//     message.Write((RakNet::MessageID) id); callback(&message);

//     auto entities = librg::streamer::query(entity);

//     for (auto other : entities) {
//         auto client = other.component<client_t>();

//         if (client) {
//             network::data.peer->Send(&message, HIGH_PRIORITY, RELIABLE_ORDERED, 0, client->address, false);
//         }
//     }
// }
