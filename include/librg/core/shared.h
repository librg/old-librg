#ifndef core_shared_h
#define core_shared_h

#include <librg/core/other.h>
#include <librg/core/constants.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <stdarg.h>
#include <functional>


namespace librg
{
    namespace core
    {
        enum rgmode {
            mode_server,
            mode_client,
        };

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
         * Set curretn tick callback
         * @param callback [description]
         */
        void set_tick_cb(std::function<void(double)> callback);

        /**
         * Set a mode for (server/client)
         * @param mode default is server
         */
        void set_mode(rgmode mode);

        /**
         * Get current mode
         * @return
         */
        rgmode get_mode();

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

#endif // core_shared_h
