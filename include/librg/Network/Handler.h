#ifndef __network_handler_h
#define __network_handler_h

#include <map>
#include <RakPeerInterface.h>
#include <BitStream.h>

#include "Client.h"

namespace Server {
namespace Network  {

const short NETWORK_PACKET_LIMIT = 256; // current limit for amount of packets introduced by the mod on top of (134) raknet packets

class Handler
{
public:
    Handler(RakNet::RakPeerInterface *peer, std::map<RakNet::RakNetGUID, Client*> *Clients);
    ~Handler();

    void Dispatch(RakNet::Packet* packet);

private:
    void OnClientConnectAttempt(RakNet::Packet* packet);
    void OnClientInit(RakNet::Packet* packet);
    void OnClientConnect(RakNet::Packet* packet);
    void OnClientDisconnect(RakNet::Packet* packet);
    void OnTest(RakNet::Packet* packet);

    void (Handler::*mRegistry[NETWORK_PACKET_LIMIT])(RakNet::Packet* packet);

    std::map<RakNet::RakNetGUID, Client*> *mClients;
    RakNet::RakPeerInterface *mPeer;
};


} // namespace Network
} // namespace Server

#endif // __network_handler_h
