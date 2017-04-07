// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_core_h
#define librg_core_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <ctime>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <unordered_map>
#include <functional>

namespace librg
{
    void core_initialize();
    void core_terminate();

    enum mode {
        mode_server,
        mode_client,
        mode_server_manual,
        mode_client_manual
    };

    namespace core
    {

        /**
         * Polling method
         * used only to get data from network
         */
        void poll();

        /**
         * Ticker
         * Used to iterate all main tickers
         * And user subscribed one
         */
        void tick();

        /**
         * Set a mode for (server/client)
         * @param mode default is server
         */
        void set_mode(mode mode);

        /**
         * Get current mode
         * @return
         */
        mode get_mode();

        /**
         * Check if current execution mode is server
         */
        static inline bool is_server() {
            return get_mode() == mode_server;
        }

        /**
         * Check if current execution mode is client
         */
        static inline bool is_client() {
            return get_mode() == mode_client;
        }

        /**
         * WARNING: UGLY
         * TODO(inlife): refactor
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
         * TODO(inlife): refactor
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
    }
}

#endif // librg_core_h
