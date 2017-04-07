// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>
#include <librg/streamer.h>

using namespace librg;

void librg::network::msg(int id, network::message_t callback)
{
    network::bitstream_t message;

    message.Write((RakNet::MessageID) GUEST_PACKET_ENUM);
    message.Write((RakNet::MessageID) id); callback(&message);

    network::data.peer->Send(&message, HIGH_PRIORITY, RELIABLE_ORDERED, 0, network::data.address, false);
}

void librg::network::msg(int id, RakNet::SystemAddress address, network::message_t callback)
{
    network::bitstream_t message;

    message.Write((RakNet::MessageID) GUEST_PACKET_ENUM);
    message.Write((RakNet::MessageID) id); callback(&message);

    network::data.peer->Send(&message, HIGH_PRIORITY, RELIABLE_ORDERED, 0, address, false);
}

void librg::network::msg(int id, entity_t entity, network::message_t callback)
{
    network::bitstream_t message;

    message.Write((RakNet::MessageID) GUEST_PACKET_ENUM);
    message.Write((RakNet::MessageID) id); callback(&message);

    auto entities = librg::streamer::query(entity);

    for (auto other : entities) {
        auto client = other.component<client_t>();

        if (client) {
            network::data.peer->Send(&message, HIGH_PRIORITY, RELIABLE_ORDERED, 0, client->address, false);
        }
    }
}
