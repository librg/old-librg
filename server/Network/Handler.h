#pragma once

namespace MOServer {
namespace Network  {


    class Handler
    {
    public:
        Handler(RakNet::RakPeerInterface *peer, std::map<RakNet::RakNetGUID, Client*> *Clients);
        ~Handler();

        void Process(RakNet::Packet* packet);

    private:
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
