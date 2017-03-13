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


