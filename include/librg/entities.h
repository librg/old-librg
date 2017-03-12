#ifndef __entities
#define __entities

#include <entityx/entityx.h>

namespace librg
{
    static entityx::EventManager*   __events;
    static entityx::EntityManager*  entities;
    static entityx::SystemManager* __systems;

    // static entityx::EntityManager* entity;

    static inline void entities_initialize()
    {
         __events = new entityx::EventManager();
         entities = new entityx::EntityManager(*__events);
        __systems = new entityx::SystemManager(*entities, *__events);

        // entity = __entity;
    }

    static inline void entities_deinitialize()
    {
        delete __systems;
        delete  entities;
        delete  __events;
    }
}

#endif // __entities
