#ifndef librg_events_default_h
#define librg_events_default_h

#include <librg/network.h>
#include <librg/entities.h>
#include <librg/components/transform.h>

namespace librg
{
    namespace events
    {
        /**
         * Default event
         * and callback type
         */
        using event_t = void;

        /**
         * Tick event
         */
        struct event_tick_t {
            uint64_t tick;
            double dt;
        };

        /**
         * Entity interpolation event (client)
         */
        struct event_inter_t {
            uint64_t guid;
            entity_t entity;
            uint8_t type;
            transform_t data;
        };

        /**
         * Log event
         */
        struct event_log_t {
            std::string output;
        };

        /**
         * Entity create event
         */
        struct event_create_t {
            uint64_t guid;
            uint8_t type;
            entity_t entity;
            network::bitstream_t* data;
        };

        using event_change_t = event_create_t;

        /**
         * Entity udpate event
         */
        using event_update_t = event_create_t;

        /**
         * Entity create event
         */
        using event_remove_t = event_create_t;

        /**
         * Client connect event
         */
        struct event_connect_t {
            entity_t entity;
        };

        /**
         * Client disconnect event
         */
        using event_disconnect_t = event_connect_t;
    }
}

#endif // librg_events_default_h
