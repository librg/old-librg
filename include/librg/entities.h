#ifndef librg_entities_h
#define librg_entities_h

#include <entityx/entityx.h>
#include <entityx/Entity.h>
#include <entityx/System.h>
#include <entityx/deps/Dependencies.h>

using namespace entityx;

namespace librg
{
    extern entityx::EventManager*   _events;
    extern entityx::EntityManager*  entities;
    extern entityx::SystemManager* _systems;

    void entities_initialize();
    void entities_terminate();
}

#endif // librg_entities_h
