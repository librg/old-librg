#include "../Handler.h"
#include "../../Core.h"

using namespace MOServer;

/**
 * Client just send us first connection
 * init packet. Its the place where we should decide
 * was or was not he banned, and does he have access to our server
 */
void Network::Handler::OnClientConnectAttempt(RakNet::Packet* packet)
{
    unsigned short  id = packet->systemAddress.systemIndex;
    std::string     ip = packet->systemAddress.ToString( true, ':' );

    Core::Log("OnClientConnectAttempt id: %d, address: %s", id, ip.c_str());
}

/**
 * Fires when user sends his username and serial
 * after he successfuly connected to raknet
 */
void Network::Handler::OnClientConnect(RakNet::Packet* packet)
{
    RakNet::BitStream bsInput(packet->data, packet->length, false);
    bsInput.IgnoreBytes(sizeof(RakNet::MessageID));

    RakNet::RakString nickName;
    bsInput.Read(nickName);

    mClients->insert(std::make_pair(
        packet->guid, new Client(nickName.C_String(), packet->systemAddress)
    ));

    Core::Log("OnClientConnect: id: %d name: %s", packet->systemAddress.systemIndex, nickName.C_String());
}

void Network::Handler::OnClientDisconnect(RakNet::Packet* packet)
{
    Core::Log("OnClientDisconnect");
}
