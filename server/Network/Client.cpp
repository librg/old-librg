#include "Client.h"

Client::Client(std::string nickName, RakNet::SystemAddress systemAddress)
    :
    mNickName(nickName),
    mSystemAddress(systemAddress)
{
    // some additional data
}

Client::~Client()
{

}
