#pragma once
#pragma once

#include "Handler.h"

namespace MOServer
{
    namespace Network
    {
        class Manager
        {
        public:
            Manager();
            ~Manager();
            void Init();
            void Tick();

            void Update();
            void Receive();

            RakNet::RakPeerInterface* GetPeer() { return mPeer; }

        private:
            RakNet::RakPeerInterface* mPeer;
            RakNet::SocketDescriptor mSocketDescriptor;
            std::map<RakNet::RakNetGUID, Client*> mClients;
            Network::Handler* mHandler;
        };
    }
}
