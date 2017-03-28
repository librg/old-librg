#include <librg/network.h>

using namespace librg;

/**
 * Idle-ticker
 * Called with very high rate, should be used
 * only to handle some light, none-blocking ops
 */
void librg::network::msg(network::messageid id, network::message_t callback)
{
    network::bitstream_t message; message.Write((RakNet::MessageID) id); callback(&message);
    network::data.peer->Send(&message, HIGH_PRIORITY, RELIABLE_ORDERED, 0, network::data.address, false);
}
