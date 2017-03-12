#ifndef network_h
#define network_h

#include <map>
#include <RakPeerInterface.h>

namespace librg
{
    static inline void network_initialize() {};
    static inline void network_terminate() {};

    namespace network
    {
        void Update(uint64_t tick);
        void Receive();

        static RakNet::RakPeerInterface* mPeer;
        static RakNet::SocketDescriptor mSocketDescriptor;
        // static std::map<RakNet::RakNetGUID, Client*> mClients;
        // static Network::Handler* mHandler;
    }
}

#endif // network_h
