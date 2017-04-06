// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_callbacks_h
#define librg_callbacks_h

#include <librg/core.h>
#include <librg/network.h>
#include <librg/entities.h>

namespace librg
{
    namespace callbacks
    {
        using evt_t = void;
        using callback_t = std::function<void(evt_t*)>;

        struct evt_tick_t { uint64_t tick; double dt; };
        struct evt_sync_t { network::bitstream_t* data, entity_t entity, int type };
        struct evt_inter_t { entity_t entity, transform_t* data };
        struct evt_create_t { uint64_t guid, uint8_t type, entity_t entity, network::bitstream_t* data };
        using  evt_update_t = evt_steamer_create_t;
        using  evt_remove_t = evt_steamer_create_t;

        enum actions {
            tick,
            sync,
            inter,
            steamer_create,
            steamer_update,
            steamer_remove,
        };

        extern std::array<actions, callback_t> handlers;

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
