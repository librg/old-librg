#include <array>
#include <librg/entities.h>

using namespace librg;

std::array<entity_callbacks::callback_t, 3> callbacks = {};

void entity_callbacks::set_create(entity_callbacks::callback_t cb) {
    callbacks[0] = cb;
}

void entity_callbacks::set_update(entity_callbacks::callback_t cb) {
    callbacks[1] = cb;
}

void entity_callbacks::set_remove(entity_callbacks::callback_t cb) {
    callbacks[2] = cb;
}

void entity_callbacks::trigger(entity_callbacks::actions action, uint64_t guid, uint8_t type, Entity entity, RakNet::BitStream* packet) {
    if (callbacks[action]) callbacks[action](guid, type, entity, packet);
}
