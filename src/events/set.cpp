// Copyright ReGuider Team, 2016-2017
//
#include <librg/events.h>

using namespace librg;

void events::set(uint64_t action, events::callback_t callback)
{
    auto it = handlers.find(action);

    if (it != handlers.end()) {
        handlers[action].push_back(callback);
    }
    else
    {
        std::vector<callback_t> handler = { callback };
        handlers[action] = handler;
    }
}
