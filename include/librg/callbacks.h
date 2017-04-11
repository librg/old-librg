// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_callbacks_h
#define librg_callbacks_h

#include <librg/core.h>
#include <librg/network.h>
#include <librg/entities.h>
#include <librg/components/transform.h>

namespace librg
{
    namespace callbacks
    {
        /**
         * Default event
         * and callback type
         */
        using evt_t = void;
        using callback_t = std::function<void(evt_t*)>;

        /**
         * Tick event
         */
        struct evt_tick_t {
            uint64_t tick;
            double dt;
        };

        /**
         * Entity interpolation event (client)
         */
        struct evt_inter_t {
            entity_t entity;
            transform_t data;
        };

        /**
         * Log event
         */
        struct evt_log_t {
            std::string output;
        };

        /**
         * Entity create event
         */
        struct evt_create_t {
            uint64_t guid;
            uint8_t type;
            entity_t entity;
            network::bitstream_t* data;
        };

        /**
         * Entity udpate event
         */
        using evt_update_t = evt_create_t;

        /**
         * Entity create event
         */
        using evt_remove_t = evt_create_t;

        /**
         * Client connect event
         */
        struct evt_connect_t {
            entity_t entity;
        };

        /**
        * Client disconnect event
        */
        using evt_disconnect_t = evt_connect_t;

        /**
         * Enum with all registered
         * event actions
         */
        enum actions {
            tick,
            inter,
            create,
            update,
            remove,
            log,
            connect,
            disconnect,
            num_of_actions
        };

        extern std::array<callback_t, num_of_actions> handlers;

        /**
         * Public Client API method
         * should be used to register handler
         * for entities which were just created and first-time synced
         * from the server (for current stream-zone)
         * @param callback
         */
        void set(actions action, callback_t callback);

        /**
         * Private method
         * Trigger particular callback
         */
        void trigger(actions action, evt_t* event);
    }
}

#endif // librg_callbacks_h
