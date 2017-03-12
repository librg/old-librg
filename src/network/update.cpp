#include <librg/network.h>

/**
 * Regulated ticker, should be used
 * to send regular messages to all connected clients
 */
void librg::network::update()
{
    // // Use a BitStream to write a custom user message
    // // Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
    // RakNet::BitStream bsOut;
    // bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
    // bsOut.Write("Hello world");
    // mPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
}
