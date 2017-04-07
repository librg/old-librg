// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/network.h>
#include <librg/network/client/connection.h>

void librg::network::client_remote_disconnect(RakNet::Packet* packet) {
    core::log("Another client has disconnected.");
}

void librg::network::client_remote_connectionlost(RakNet::Packet* packet) {
    core::log("Another client has lost the connection.");
}

void librg::network::client_remote_newincoming(RakNet::Packet* packet) {
    core::log("Another client has connected.");
}

void librg::network::client_new_incoming_connection(RakNet::Packet* packet) {
    core::log("A connection is incoming.");
}

void librg::network::client_no_free_incoming_connections(RakNet::Packet* packet) {
    core::log("The server is full.");
}

void librg::network::client_disconnect_notification(RakNet::Packet* packet) {
    core::log("disconnected.");
}

void librg::network::client_connection_lost(RakNet::Packet* packet) {
    core::log("Connection lost.");
}

void librg::network::client_connection_request_accepted(RakNet::Packet* packet)
{
    core::log("Sending name, and serial");

    network::data.address = packet->systemAddress;

    /**
    * This data-packet is used to validate
    * game mod compability, and add client to server list
    *
    * Data template
    * @param int NETWORK_PLATFORM_ID
    * @param int NETWORK_PROTOCOL_VERSION
    * @param int NETWORK_BUILD_VERSION
    * @param string Client Name
    */
    RakNet::BitStream data;
    data.Write((RakNet::MessageID)CONNECTION_INIT);
    data.Write(NETWORK_PLATFORM_ID);
    data.Write(NETWORK_PROTOCOL_VERSION);
    data.Write(NETWORK_BUILD_VERSION);
    data.Write("Test Player");
    data.Write("4555ASDASD4555ASDASD4555");
    network::data.peer->Send(&data, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
}

void librg::network::client_connection_success(RakNet::Packet* packet) {
    core::log("Connection succeeded, we are now on the server");
}