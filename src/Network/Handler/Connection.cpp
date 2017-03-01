#include <Core.h>
#include <Network/Handler.h>
#include <Shared/BuildVersion.h>
#include <Shared/MessageID.h>

// #include "Connection.h"

using namespace Server;

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
 *
 * Packet structure
 * @param int MOSERVER_PROTOCOL_VERSION
 * @param int MOSERVER_BUILD_VERSION
 * @param string Client name
 * @param string Client serial
 */
void Network::Handler::OnClientConnect(RakNet::Packet* packet)
{
    RakNet::BitStream bsOutput;
    RakNet::BitStream bsInput(packet->data, packet->length, false);
    bsInput.IgnoreBytes(sizeof(RakNet::MessageID));

    int protocolVersion = -1, buildVersion = -1, platformId = -1;
    bsInput.Read(platformId);
    bsInput.Read(protocolVersion);
    bsInput.Read(buildVersion);

    // incompatible protocol version - force immidiate disconnect
    if (protocolVersion != NETWORK_PROTOCOL_VERSION || platformId != NETWORK_PLATFORM_ID) {
        bsOutput.Write(static_cast<RakNet::MessageID>(MessageID::CONNECTION_REFUSED));
        bsOutput.Write("Incompatible game version.");

        mPeer->Send(&bsOutput, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

        Core::Log("OnClientConnect: refsued ip: %s, reason: incompatible game version.", packet->systemAddress.ToString(true, ':'));
        return;
    }

    // let server owner to decide, to kick or not to kick
    if (buildVersion != NETWORK_BUILD_VERSION) {
        // TODO(inlife): add check for server parameters to decide, should be connection refused or allowed
        bsOutput.Write(static_cast<RakNet::MessageID>(MessageID::CONNECTION_REFUSED));
        bsOutput.Write("Incompatible build version.");

        mPeer->Send(&bsOutput, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

        Core::Log("OnClientConnect: refsued ip: %s, reason: incompatible build version.", packet->systemAddress.ToString(true, ':'));
        return;
    }

    RakNet::RakString nickName;
    bsInput.Read(nickName);

    RakNet::RakString serial;
    bsInput.Read(serial);

    mClients->insert(std::make_pair(
        packet->guid, new Client(nickName.C_String(), packet->systemAddress, serial.C_String())
    ));

    // send success
    bsOutput.Write(static_cast<RakNet::MessageID>(MessageID::CONNECTION_ACCEPTED));
    mPeer->Send(&bsOutput, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

    // Game::Manager::Instance()->Trigger(1, packet);
    // Event::Manager::Instance()->Dispatch("OnClientConnect", EVENT_PARAM(new OnClientConnectData{ packet }, [=](HSQUIRRELVM vm){
    //     auto array = new Sqrat::Array(vm);
    //     array->Append(packet);
    //     return array;
    // }));
    // Core::Log("OnClientConnect: id: %d name: %s serial: %s", packet->systemAddress.systemIndex, nickName.C_String(), serial.C_String());
    return;
}

/**
 * On client disconnect
 */
void Network::Handler::OnClientDisconnect(RakNet::Packet* packet)
{
    // Event::Manager::Instance()->Dispatch("OnClientDisconnect", EVENT_PARAM(new OnClientConnectData{ packet }, [=](HSQUIRRELVM vm){
    //     auto array = new Sqrat::Array(vm);
    //     array->Append(packet);
    //     return array;
    // }));

    Core::Log("OnClientDisconnect: id: %d", packet->systemAddress.systemIndex);
}
