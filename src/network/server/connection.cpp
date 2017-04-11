// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/callbacks.h>
#include <librg/network.h>
#include <librg/streamer.h>
#include <librg/components/client.h>
#include <librg/components/streamable.h>
#include <librg/components/transform.h>
#include <librg/network/server/connection.h>

/**
* Client just send us first connection
* init packet. Its the place where we should decide
* was or was not he banned, and does he have access to our server
*/
void librg::network::server_new_incoming_connection(RakNet::Packet* packet)
{
    unsigned short id = packet->systemAddress.systemIndex;
    std::string    ip = packet->systemAddress.ToString(true, ':');

    core::log("server_new_incoming_connection id: %d, address: %s", id, ip.c_str());
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
void librg::network::server_connect(RakNet::Packet* packet)
{
    RakNet::BitStream output;
    RakNet::BitStream input(packet->data, packet->length, false);
    input.IgnoreBytes(sizeof(RakNet::MessageID));

    uint16_t protocolVersion = -1, buildVersion = -1, platformId = -1;
    input.Read(platformId);
    input.Read(protocolVersion);
    input.Read(buildVersion);

    // incompatible protocol version - force immidiate disconnect
    if (protocolVersion != network::protoVersion || platformId != network::platformId) {
        output.Write(static_cast<RakNet::MessageID>(CONNECTION_REFUSED));
        output.Write("Incompatible game version.");

        data.peer->Send(&output, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

        core::log("server_connect: refsued ip: %s, reason: incompatible game version.", packet->systemAddress.ToString(true, ':'));
        return;
    }

    // let server owner to decide, to kick or not to kick
    if (buildVersion != network::buildVersion) {
        // TODO(inlife): add check for server parameters to decide, should be connection refused or allowed
        output.Write(static_cast<RakNet::MessageID>(CONNECTION_REFUSED));
        output.Write("Incompatible build version.");

        data.peer->Send(&output, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

        core::log("server_connect: refsued ip: %s, reason: incompatible build version.", packet->systemAddress.ToString(true, ':'));
        return;
    }

    RakNet::RakString nickName;
    input.Read(nickName);

    RakNet::RakString serial;
    input.Read(serial);

    // for (int i = 0; i < 5; ++i) {
    auto entity = entities->create();
    entity.assign<streamable_t>();
    entity.assign<transform_t>();

    // if (i == 1) {
    entity.assign<client_t>(packet->systemAddress, nickName.C_String(), serial.C_String());
    network::clients.insert(std::make_pair(packet->guid, entity));
    // }
    // }

    // send success
    output.Write(static_cast<RakNet::MessageID>(CONNECTION_ACCEPTED));
    data.peer->Send(&output, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

    auto event = callbacks::evt_connect_t{ entity };
    callbacks::trigger(callbacks::connect, (callbacks::evt_t*)&event);

    core::log("server_connect: id: %d name: %s serial: %s", packet->systemAddress.systemIndex, nickName.C_String(), serial.C_String());
    return;
}

/**
* On client disconnect
*/
void librg::network::server_disconnect(RakNet::Packet* packet)
{
    // Event::Manager::Instance()->Dispatch("OnClientDisconnect", EVENT_PARAM(new OnClientConnectData{ packet }, [=](HSQUIRRELVM vm){
    //     auto array = new Sqrat::Array(vm);
    //     array->Append(packet);
    //     return array;
    // }));

    if (clients.find(packet->guid) != clients.end()) {
        auto entity = clients[packet->guid];
        
        auto event = callbacks::evt_disconnect_t{ entity };
        callbacks::trigger(callbacks::disconnect, (callbacks::evt_t*)&event);

        streamer::remove(clients[packet->guid]);
        clients.erase(packet->guid);
    }

    core::log("server_disconnect: id: %d", packet->systemAddress.systemIndex);
}
