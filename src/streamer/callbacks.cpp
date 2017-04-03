// Copyright ReGuider Team, 2016-2017
//
#include <array>
#include <librg/streamer.h>

using namespace librg;

std::unordered_map<uint64_t, Entity> streamer_callbacks::client_cache = {};
std::array<streamer_callbacks::callback_t, 4> client_callbacks = {};

void streamer_callbacks::set(
    streamer_callbacks::actions action,
    streamer_callbacks::callback_t cb
) {
    client_callbacks[action] = cb;
}

void streamer_callbacks::trigger(
    streamer_callbacks::actions action,
    uint64_t guid,
    uint8_t type,
    Entity entity,
    void* data
) {
    if (client_callbacks[action]) {
        client_callbacks[action](guid, type, entity, data);
    }
}
