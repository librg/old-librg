// Copyright ReGuider Team, 2016-2017
//
#include <enet/enet.h>

#include <librg/core.h>
#include <librg/events.h>
#include <librg/streamer.h>
#include <librg/network.h>
#include <librg/network/controllers.h>
#include <librg/components/client.h>
#include <librg/components/streamable.h>
#include <librg/components/transform.h>

using namespace librg;

void network::connection_controller::init(network::peer_t* peer, network::packet_t* packet, uint8_t channel)
{
    char my_host[16];

    enet_address_get_host_ip(&peer->address, my_host, 16);
    core::log("a new connection attempt at %s:%u.\n", my_host, peer->address.port);

    if (core::is_client()) {
        /**
         * Send connection request packet
         */
        network::msg(network::connection_request, peer, [](bitstream_t* message) {
            message->write((uint8_t) 1);
            message->write((uint8_t) 1);
            message->write((uint8_t) 1);

            message->write("Test Player");
            message->write("4555ASDASD4555ASDASD4555");
        });
    }
}

void network::connection_controller::request(network::peer_t* peer, network::packet_t* packet, uint8_t channel)
{
    bitstream_t output;
    bitstream_t input;

    uint16_t id = 0;

    input.set_raw(packet->data);
    input.read(id);

    uint8_t protocolVersion = 0, buildVersion = 0, platformId = 0;
    input.read(platformId);
    input.read(protocolVersion);
    input.read(buildVersion);

    core::log("%d", platformId);

    // // incompatible protocol version - force immidiate disconnect
    // if (protocolVersion != network::protoVersion || platformId != network::platformId) {
    //     output.Write(static_cast<RakNet::MessageID>(CONNECTION_REFUSED));
    //     output.Write("Incompatible game version.");

    //     data.peer->Send(&output, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

    //     core::log("server_connect: refsued ip: %s, reason: incompatible game version.", packet->systemAddress.ToString(true, ':'));
    //     return;
    // }

    // // let server owner to decide, to kick or not to kick
    // if (buildVersion != network::buildVersion) {
    //     // TODO(inlife): add check for server parameters to decide, should be connection refused or allowed
    //     output.Write(static_cast<RakNet::MessageID>(CONNECTION_REFUSED));
    //     output.Write("Incompatible build version.");

    //     data.peer->Send(&output, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

    //     core::log("server_connect: refsued ip: %s, reason: incompatible build version.", packet->systemAddress.ToString(true, ':'));
    //     return;
    // }

    // RakNet::RakString nickName;
    // input.read(nickName);

    // RakNet::RakString serial;
    // input.read(serial);

    auto entity = entities->create();
    entity.assign<streamable_t>();
    entity.assign<transform_t>();
    entity.assign<client_t>(peer, "nonono", "anananana");

    // send success
    network::connected_peers.insert(std::make_pair(peer, entity));
    network::msg(network::connection_accept, peer, nullptr);
    events::trigger(events::on_connect, new events::event_connect_t{ entity });

    core::log("connect: id: %ld name: %s serial: %s", peer->connectID, "nonono", "anananana");
}

void network::connection_controller::accept(network::peer_t* peer, network::packet_t* packet, uint8_t channel)
{
    core::log("connection acccepted");
}

void network::connection_controller::refuse(network::peer_t* peer, network::packet_t* packet, uint8_t channel)
{
    core::log("connection refused");
}

void network::connection_controller::disconnect(network::peer_t* peer, network::packet_t* packet, uint8_t channel)
{
    core::log("something disconnected");

    if (connected_peers.find(peer) != connected_peers.end()) {
        events::trigger(events::on_disconnect, new event_disconnect_t{ connected_peers[peer] });
        streamer::remove(connected_peers[peer]);
        connected_peers.erase(peer);
    }
}