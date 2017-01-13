#pragma once

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
            // std::map<RakNet::RakNetGUID, Client*> mClients;
            RakNet::RakPeerInterface* mPeer;
            // RakNet::SocketDescriptor mSocketDescriptor;
        };
    }
}
