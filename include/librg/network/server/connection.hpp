#ifndef librg_network_server_connection_hpp
#define librg_network_server_connection_hpp

#include <librg/network.h>
#include <librg/streamer.h>
#include <librg/components/client.h>
#include <librg/components/streamable.h>
#include <librg/components/transform.h>
#include <librg/core/shared.h>

namespace librg
{
    namespace network
    {
        /**
         * Client just send us first connection
         * init packet. Its the place where we should decide
         * was or was not he banned, and does he have access to our server
         */
        static inline void server_new_incoming_connection(RakNet::Packet* packet)
        {
            unsigned short id = packet->systemAddress.systemIndex;
            std::string    ip = packet->systemAddress.ToString( true, ':' );

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
        static inline void server_connect(RakNet::Packet* packet)
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

                data.peer->Send(&bsOutput, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

                core::log("server_connect: refsued ip: %s, reason: incompatible game version.", packet->systemAddress.ToString(true, ':'));
                return;
            }

            // let server owner to decide, to kick or not to kick
            if (buildVersion != NETWORK_BUILD_VERSION) {
                // TODO(inlife): add check for server parameters to decide, should be connection refused or allowed
                bsOutput.Write(static_cast<RakNet::MessageID>(MessageID::CONNECTION_REFUSED));
                bsOutput.Write("Incompatible build version.");

                data.peer->Send(&bsOutput, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

                core::log("server_connect: refsued ip: %s, reason: incompatible build version.", packet->systemAddress.ToString(true, ':'));
                return;
            }

            RakNet::RakString nickName;
            bsInput.Read(nickName);

            RakNet::RakString serial;
            bsInput.Read(serial);

            auto entity = entities->create();
            entity.assign<streamable_t>();
            entity.assign<transform_t>();
            entity.assign<client_t>(packet->systemAddress, nickName.C_String(), serial.C_String());
            network::clients.insert(std::make_pair(packet->guid, entity));

            // send success
            bsOutput.Write(static_cast<RakNet::MessageID>(MessageID::CONNECTION_ACCEPTED));
            data.peer->Send(&bsOutput, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

            // Game::Manager::Instance()->Trigger(1, packet);
            // Event::Manager::Instance()->Dispatch("OnClientConnect", EVENT_PARAM(new OnClientConnectData{ packet }, [=](HSQUIRRELVM vm){
            //     auto array = new Sqrat::Array(vm);
            //     array->Append(packet);
            //     return array;
            // }));
            core::log("server_connect: id: %d name: %s serial: %s", packet->systemAddress.systemIndex, nickName.C_String(), serial.C_String());
            return;
        }

        /**
         * On client disconnect
         */
        static inline void server_disconnect(RakNet::Packet* packet)
        {
            // Event::Manager::Instance()->Dispatch("OnClientDisconnect", EVENT_PARAM(new OnClientConnectData{ packet }, [=](HSQUIRRELVM vm){
            //     auto array = new Sqrat::Array(vm);
            //     array->Append(packet);
            //     return array;
            // }));

            if (clients.find(packet->guid) != clients.end()) {
                streamer::remove(clients[packet->guid]);
                clients[packet->guid].destroy();
                clients.erase(packet->guid);
            }

            core::log("server_disconnect: id: %d", packet->systemAddress.systemIndex);
        }
    }
}

#endif // librg_network_server_connection_hpp
