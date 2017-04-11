// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_events_h
#define librg_events_h

#include <functional>
#include <uv.h>
#include <librg/core.h>

namespace librg
{
    void events_initialize();
    void events_terminate();

    namespace events
    {
        using evt_t = void;
        using callback_t = std::function<void(evt_t*)>;

        extern std::unordered_map<uint64_t, std::vector<callback_t>> handlers;

        /**
         * Public API method
         * used to register custom event handlers
         * @param action
         * @param callback
         */
        void set(uint64_t action, callback_t callback);

        /**
         * Public API method
         * used to trigger particular callback
         */
        void trigger(uint64_t action, evt_t* event);
    }
}

#endif // librg_events_h
