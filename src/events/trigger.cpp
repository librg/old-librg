// Copyright ReGuider Team, 2016-2017
//
#include <librg/events.h>

using namespace librg;

void events::trigger(uint64_t action, events::evt_t* event)
{
    auto it = handlers.find(action);
    if (it == handlers.end()) return;

    for (auto handler : it->second) {
        handler(event);
    }
}
