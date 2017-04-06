// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_h
#define librg_h

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4312)
#pragma warning(disable:4577)
#endif

#if WIN32
#include <windows.h>
inline void uv_sleep(int milis) {
    Sleep(milis);
}
#else
#include <unistd.h>
inline void uv_sleep(int milis) {
    usleep(milis * 1000);
}
#endif

// Copyright ReGuider Team, 2016-2017
//
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

/**
 * All includes
 */
#include <librg/core.h>
#include <librg/callbacks.h>
#include <librg/entities.h>
#include <librg/events.h>
#include <librg/network.h>
#include <librg/resources.h>
#include <librg/streamer.h>


#endif // librg_h
