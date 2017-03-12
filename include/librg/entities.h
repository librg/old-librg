#ifndef entities_h
#define entities_h

#include <entityx/entityx.h>

namespace librg
{
    extern entityx::EventManager*   __events;
    extern entityx::EntityManager*  entities;
    extern entityx::SystemManager* __systems;

    void entities_initialize();
    void entities_terminate();
}

#endif // entities_h
