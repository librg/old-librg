#ifndef _m2o_network_manager
#define _m2o_network_manager

#include <map>
#include <RakPeerInterface.h>
#include "Client.h"
#include "Handler.h"

namespace M2OServer {
namespace Network  {


class Manager : public Singleton<Manager>
{
    friend class Singleton<Manager>;

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


} // Netwrok
} // M2OServer

#endif // _m2o_network_manager
