#include <librg/Entity/Manager.h>

using namespace Server;

entity_id Entity::Manager::Create(int64_t type) {
    for(auto i = 0; i < MAX_ENTITIES; ++i) {
        auto entity = &mEntities.at(i);

        if(entity->index == -1) {
            entity->index = i;

            if(entity->type != type) {
                delete entity->data;
            }
            entity->type = type;

            return *entity;
        }
    }

    return InvalidEntity;
}

void Entity::Manager::Destroy(entity_id oldEntity) {
    auto entity = Get(oldEntity);
    entity->genid++;
    entity->index = -1;
}

void Entity::Manager::AttachData(entity_id entity, void* data) {
    auto e = Get(entity);
    e->data = data;
}

void Entity::Manager::DetachData(entity_id entity) {
    auto e = Get(entity);
    e->data = nullptr;
}

entity_id* Entity::Manager::Get(entity_id oldEntity) {
    try {
        auto entity = &mEntities.at(oldEntity.index);
        if(entity->genid == oldEntity.genid) {
            return entity;
        }
    } catch (std::exception ex) {
        // TODO(zaklaus): Print error...
    }

    return nullptr;
}
