#ifndef __entity_manager
#define __entity_manager

#include <librg/Utils/Singleton.h>

#include <entityx/entityx.h>

namespace Server {
namespace Entity {

namespace Manager {
    static inline entityx::EntityManager* Instance()
    {
        static entityx::EventManager events;
        static entityx::EntityManager entities(events);
        return &entities;
    }
}

} // Entity
} // Server

#endif // __entity_manager
