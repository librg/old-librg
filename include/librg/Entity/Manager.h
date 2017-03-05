#ifndef __entity_manager
#define __entity_manager

#include <librg/Utils/Singleton.h>

#include <entityx/entityx.h>

namespace Server {
namespace Entity {

namespace Manager {
    static inline entityx::EventManager* GetEvents()
    {
        static entityx::EventManager events;
        return &events;
    }

    static inline entityx::EntityManager* Instance()
    {
        auto events = GetEvents();
        static entityx::EntityManager entities(*events);
        return &entities;
    }

    static inline entityx::SystemManager* GetSystems()
    {
        auto entities = Instance();
        auto events = GetEvents();
        static entityx::SystemManager systems(*entities, *events);
        return &systems;
    }
}

} // Entity
} // Server

#endif // __entity_manager
