// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>

using namespace librg;

/**
 * Idle-ticker
 * Called with very high rate, should be used
 * only to handle some light, none-blocking ops
 */
void librg::network::msg(int id, network::message_t callback)
{
    network::bitstream_t message; message.Write((RakNet::MessageID) GUEST_PACKET_ENUM);  message.Write((RakNet::MessageID) id); callback(&message);
    network::data.peer->Send(&message, HIGH_PRIORITY, RELIABLE_ORDERED, 0, network::data.address, false);
}
