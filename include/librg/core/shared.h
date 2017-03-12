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

#ifndef core_shared_h
#define core_shared_h

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>

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

#include <librg/entities.h>
#include <librg/events.h>
#include <librg/network.h>
#include <librg/resources.h>

namespace librg
{
    namespace core
    {
        static uint64_t counter = 0;

        /**
         * WARNING: UGLY
         */
        static inline void error(const char* format, ...)
        {
            va_list ap;
            char message[1024] = { 0 };
            va_start(ap, format);
            vsprintf(message, format, ap);
            va_end(ap);

            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);
            // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
            // for more information about date/time format
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

            // TODO(inlife): move to async trigger -> callback
            printf("[SERVER][%s] - %s\n", buf, message);
        }

        /**
         * WARNING: UGLY
         */
        static inline void log(const char* format, ...)
        {
            va_list ap;
            char message[1024] = { 0 };
            va_start(ap, format);
            vsprintf(message, format, ap);
            va_end(ap);

            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);
            // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
            // for more information about date/time format
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

            // TODO(inlife): move to async trigger -> callback
            printf("[SERVER][%s] - %s\n", buf, message);
        }

        /**
         * [set_tick_cb description]
         * @param callback [description]
         */
        void set_tick_cb(std::function<void(double)> callback);
        void tick();
        void poll();
    }
}

#endif // core_shared_h
