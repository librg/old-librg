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
// #include <windows.h>
inline void uv_sleep(int milis) {
    // Sleep(milis);
}
#else
#include <unistd.h>
inline void uv_sleep(int milis) {
    usleep(milis * 1000);
}
#endif

/**
 * All includes
 */
#include <librg/core.h>
#include <librg/callbacks.h>
#include <librg/entities.h>
#include <librg/network.h>
#include <librg/resources.h>
#include <librg/streamer.h>


#endif // librg_h
