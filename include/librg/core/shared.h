/**
 * Random number setting current game platform id
 * to prevent connections from different games/mods, in future
 */
#ifndef NETWORK_PLATFORM_ID
#define NETWORK_PLATFORM_ID 1
#endif

/**
 * Version of protocol, should be changed if major, incompatible changes are introduced
 */
#ifndef NETWORK_PROTOCOL_VERSION
#define NETWORK_PROTOCOL_VERSION 1
#endif

/**
 * version of build. server owner can decide,
 * should clients should be refused or allowed joining the game
 */
#ifndef NETWORK_BUILD_VERSION
#define NETWORK_BUILD_VERSION 1
#endif


#ifndef __core_shared
#define __core_shared

#include "MessageIdentifiers.h"

namespace MessageID
{
    enum MainIDS {
        CONNECTION_INIT = ID_USER_PACKET_ENUM + 1,
        CONNECTION_REFUSED,
        CONNECTION_ACCEPTED,
        CONNECTION_DISCONNECTED,
        PLAYER_SYNC_ONFOOT,
        PLAYER_EVENT_CREATE,
    };
};



namespace librg
{
    namespace core
    {
        static uint64_t counter = 0;

        void error(std::string msg, ...)
        {
            // todo
        }

        void log(std::string msg, ...)
        {
            // todo
        }
    }
}






#endif // __core_shared
