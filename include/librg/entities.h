#ifndef entities_h
#define entities_h

#include <entityx/entityx.h>

namespace librg
{
    extern entityx::EventManager*   _events;
    extern entityx::EntityManager*  entities;
    extern entityx::SystemManager* _systems;

    void entities_initialize();
    void entities_terminate();
}

#endif // entities_h
