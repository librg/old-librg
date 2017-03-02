#ifndef __entity_system
#define __entity_system

#include <Utils/Singleton.h>

#include <array>

enum
{
    EntityType_Unknown = -1,
    EntityType_FirstFree = 42,
};

#define MAX_ENTITIES 32768

struct entity_id
{
    int64_t index;
    int64_t genid; // NOTE(zaklaus): Generation ID
    int64_t type;
    void*   data;
};

entity_id InvalidEntity = {-1,-1,-1,nullptr};

namespace Server {
namespace Entity {

class Manager : public Singleton<Manager>
{
    friend class Singleton<Manager>;

public:
    Manager() = default;
    ~Manager() = default;
    void Init();

    /**
    * Public API method for creating an entity.
    */
    entity_id Create(int64_t type);

    /**
    * Public API method for destroying an entity.
    * @param    oldEntity  An entity to destroy.
    */
    void Destroy(entity_id oldEntity);

    /**
    * Public API method for attaching data to the entity.
    * @param    entity  An entity to attach to.
    * @param    data    Data to attach.
    */
    void AttachData(entity_id entity, void* data);

    /**
    * Public API method for detaching data from the entity.
    * @note Caller handles data de-allocation.
    * @param    entity  An entity to detach from.
    */
    void DetachData(entity_id entity);

private:
    entity_id* Get(entity_id entity);

    std::array<entity_id, MAX_ENTITIES> mEntities;
};

} // Entity
} // Server

#endif
