#ifndef __network_manager
#define __network_manager

#include <map>

#include <RakPeerInterface.h>
#include <Utils/Singleton.h>

#include "Client.h"
#include "Handler.h"

namespace Server::Network {
    class Manager : public Singleton<Manager>
    {
        friend class Singleton<Manager>;

    public:
        Manager();
        ~Manager();
        void Init();
        void Tick();

        void Update(uint64_t tick);
        void Receive();

        RakNet::RakPeerInterface* GetPeer() { return mPeer; }

    private:
        RakNet::RakPeerInterface* mPeer;
        RakNet::SocketDescriptor mSocketDescriptor;
        std::map<RakNet::RakNetGUID, Client*> mClients;
        Network::Handler* mHandler;
    };
}

#endif // __network_manager
