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
            uint64_t guid;
            entity_t entity;
            uint8_t type;
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

        using evt_change_t = evt_create_t;

        /**
         * Client/Server start event
         */
        struct evt_start_t {
            uint32_t _unused0;
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
            start,
            num_of_actions
        };

        extern std::unordered_map<uint64_t, std::vector<callback_t>> handlers;

        /**
         * Public API method
         * Sets callback for particular native event.
         * @param action
         * @param callback
         */
        void set(actions action, callback_t callback);

        /**
        * Public API method
        * Adds event handler to a custom event.
        * @param action
        * @param callback
        */
        static inline void add(actions action, callback_t callback) {
            set((callbacks::actions)(callbacks::num_of_actions + action), callback);
        }

        /**
         * Public API method
         * Triggers particular callback
         * Directly used ONLY for natives!
         * @param action
         * @param event
         */
        void trigger(actions action, evt_t* event);

        /**
        * Public API method
        * Triggers all registered event handlers of a particular custom event.
        * @param action
        * @param event
        */
        static inline void trigger_custom(actions action, evt_t* event) {
            trigger((callbacks::actions)(callbacks::num_of_actions + action), event);
        }
    }
}

#endif // librg_callbacks_h
