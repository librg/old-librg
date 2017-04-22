// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_events_h
#define librg_events_h

#include <librg/events/default.h>

#ifndef LIBRG_EVENT_HANDLERS
#define LIBRG_EVENT_HANDLERS 2048
#endif

namespace librg
{
    namespace events
    {
        using callback_t = std::function<void(event_t*)>;

        /**
         * Adds a callback listener to a particular event
         * @param event id. for custom events, id should be >= last_event_number
         * @param callback
         */
        void add(uint16_t id, callback_t callback);

        /**
         * Sets event listener with a particular slot
         * @param event id same as in add method
         * @param slot on which we should insert the event
         * @param callback
         */
        bool set(uint16_t id, size_t slot, callback_t callback);

        /**
         * Shortcut for set method saving in slot 0
         * @param event id same as in add method
         * @param callback
         */
        bool set(uint16_t id, callback_t callback);

        /**
         * Triggers particular callback
         * @param event id
         * @param event
         */
        void trigger(uint16_t id, event_t* event);

        /**
         * Templated shourcut trigger
         * @param event id
         * @param event
         */
        template<typename T>
        static inline void trigger(uint16_t id, T* event) {
            trigger(id, (event_t*) event);
        }

        /**
         * Storage for our event callbacks
         */
        extern std::array<std::vector<callback_t>, LIBRG_EVENT_HANDLERS> event_handlers;
    }
}

#endif // librg_events_h
