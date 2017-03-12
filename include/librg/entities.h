#ifndef entities_h
#define entities_h

#include <entityx/entityx.h>

namespace librg
{
    static entityx::EventManager*   __events;
    static entityx::EntityManager*  entities;
    static entityx::SystemManager* __systems;

    static inline void entities_initialize()
    {
         __events = new entityx::EventManager();
         entities = new entityx::EntityManager(*__events);
        __systems = new entityx::SystemManager(*entities, *__events);
    }

    static inline void entities_terminate()
    {
        delete __systems;
        delete  entities;
        delete  __events;
    }
}

#endif // entities_h
