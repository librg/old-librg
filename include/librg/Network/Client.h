#ifndef __network_client
#define __network_client

#include <RakPeerInterface.h>
#include <string>

class Client
{
public:
    Client(std::string nickName, RakNet::SystemAddress systemAddress, std::string serial);
    ~Client();

    // Player* GetPlayer() { return mPlayer; }

private:
    RakNet::SystemAddress mSystemAddress;
    std::string mNickName;
    std::string mSerial;
    // Player* mPlayer;
};

#endif // __network_client
