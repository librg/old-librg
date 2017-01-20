#include "../../stdinc.h"

using namespace MOServer;

Network::Handler::Handler(RakNet::RakPeerInterface *peer, std::map<RakNet::RakNetGUID, Client*> *Clients)
    : mPeer(peer)
    , mClients(Clients)
{
    // connection stuff
    mRegistry[MessageID::CONNECTION_INIT]       =   &Handler::OnClientConnect;
    mRegistry[ID_CONNECTION_LOST]               =   &Handler::OnClientDisconnect;
    mRegistry[ID_DISCONNECTION_NOTIFICATION]    =   &Handler::OnClientDisconnect;

    // player stuff
    // mRegistry[MessageID::PLAYER_SYNC_ONFOOT]    =   &Handler::OnPlayerFootSync;

    // vehicle stuff
};

Network::Handler::~Handler() {};

void Network::Handler::Process(RakNet::Packet* packet)
{
    RakNet::MessageID id = packet->data[0];

    if (mRegistry[id]) {
        (*this.*mRegistry[id])(packet);
    }
};

void Network::Handler::OnTest(RakNet::Packet* packet)
{
    Core::Instance()->Log("called OnTest");
}
