#ifndef librg_entities_h
#define librg_entities_h

#include <entityx/entityx.h>
#include <entityx/Entity.h>
#include <entityx/System.h>
#include <entityx/deps/Dependencies.h>
#include <BitStream.h>

using namespace entityx;

namespace librg
{
    extern entityx::EventManager*   _events;
    extern entityx::EntityManager*  entities;
    extern entityx::SystemManager* _systems;

    void entities_initialize();
    void entities_terminate();

    namespace entity_callbacks
    {
        using callback_t = std::function<void(uint64_t, uint8_t, Entity, RakNet::BitStream *)>;

        enum actions {
            create,
            update,
            remove,
        };

        /**
         * Public Client API method
         * should be used to register handler
         * for entities which were just created and first-time synced
         * from the server (for current stream-zone)
         * @param callback
         */
        void set_create(callback_t callback);

        /**
         * Public Client API method
         * should be used to register handler
         * for entities which were updated in current stream-zone
         * @param callback
         */
        void set_update(callback_t callback);

        /**
         * Public Client API method
         * should be used to register handler
         * for entities which were removed from current stream-zone
         * @param callback
         */
        void set_remove(callback_t callback);

        /**
         * Private method
         */
        void trigger(actions action, uint64_t, uint8_t, Entity, RakNet::BitStream *);
    }
}

#endif // librg_entities_h
