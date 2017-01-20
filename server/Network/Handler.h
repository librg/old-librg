#ifndef _mo_network_handler_h
#define _mo_network_handler_h

#include <map>

#include <MessageID.h>
#include <MessageIdentifiers.h>
#include <RakPeerInterface.h>
#include <BitStream.h>
#include <BuildVersion.h>

#include "Client.h"

namespace MOServer {
namespace Network  {


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

    void (Handler::*mRegistry[MOSERVER_PACKET_LIMIT])(RakNet::Packet* packet);

    std::map<RakNet::RakNetGUID, Client*> *mClients;
    RakNet::RakPeerInterface *mPeer;
};


} // namespace Network
} // namespace MOServer

#endif // _mo_network_handler_h
