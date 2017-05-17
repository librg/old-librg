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
using namespace librg::network;

void connection_controller::init(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    char my_host[16];

    enet_address_get_host_ip(&peer->address, my_host, 16);
    core::log("a new connection attempt at %s:%u.\n", my_host, peer->address.port);

    if (core::is_client()) {
        /**
         * Send connection request packet
         */
        network::msg(connection_request, peer, [](bitstream_t* message) {
            message->write_uint8(core::config.platform_id);
            message->write_uint8(core::config.proto_version);
            message->write_uint8(core::config.build_version);

            message->write_cstr("Test Player");
            message->write_cstr("4555ASDASD4555ASDASD4555");
        });
    }
}

void connection_controller::request(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    bitstream_t output;

    uint8_t protocolVersion = 0, buildVersion = 0, platformId = 0;
    data->read(platformId);
    data->read(protocolVersion);
    data->read(buildVersion);

    core::log("%d", platformId);

    auto platform_id   = data->read_uint8();
    auto proto_version = data->read_uint8();
    auto build_version = data->read_uint8();

    // // incompatible protocol version - force immidiate disconnect
    // if (proto_version != core::config.proto_version || platform_id != core::config.platform_id) {
    //     output.Write(static_cast<RakNet::MessageID>(CONNECTION_REFUSED));
    //     output.Write("Incompatible game version.");

    //     data.peer->Send(&output, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

    //     core::log("server_connect: refsued ip: %s, reason: incompatible game version.", packet->systemAddress.ToString(true, ':'));
    //     return;
    // }

    // // let server owner to decide, to kick or not to kick
    // if (buildVersion != buildVersion) {
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
    connected_peers.insert(std::make_pair(peer, entity));
    msg(connection_accept, peer, nullptr);
    events::trigger(events::on_connect, new events::event_connect_t{ entity });

    core::log("connect: id: %ld name: %s serial: %s", peer->connectID, "nonono", "anananana");
}

void connection_controller::accept(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    connected_peers.insert(std::make_pair(peer, entities->create()));
    core::log("connection acccepted");
}

void connection_controller::refuse(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    core::log("connection refused");
}

void connection_controller::disconnect(peer_t* peer, packet_t* packet, bitstream_t* data)
{
    core::log("something disconnected");

    if (connected_peers.find(peer) != connected_peers.end()) {
        events::trigger(events::on_disconnect, new events::event_disconnect_t{ connected_peers[peer] });
        streamer::remove(connected_peers[peer]);
        connected_peers.erase(peer);
    }
}
