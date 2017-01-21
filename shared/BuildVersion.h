#ifndef _mo_build_version
#define _mo_build_version

// #define MOSERVER_MOD_ID             121 // random number setting current game mod id, to prevent connections from different games/mods
#define MO_PROTOCOL_VERSION     1   // version of protocol, should be changed if major, incompatible changes are introduced
#define MO_BUILD_VERSION        1   // version of build. server owner can decide, should clients should be refused or allowed joining the game
#define MO_PACKET_LIMIT         256 // current limit for amount of packets introduced by the mod on top of (134) raknet packets

#endif // _mo_build_version
