#include "../../stdinc.h"

using namespace MOServer;

void Network::Handler::OnClientConnect(RakNet::Packet* packet)
{
    Core::Log("onOnClientConnect");
}

void Network::Handler::OnClientDisconnect(RakNet::Packet* packet)
{
    Core::Log("onOnClientDisconnect");
}
