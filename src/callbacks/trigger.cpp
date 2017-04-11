// Copyright ReGuider Team, 2016-2017
//
#include <librg/callbacks.h>

using namespace librg;

void callbacks::trigger(callbacks::actions action, callbacks::evt_t* event)
{
    if (action < callbacks::num_of_actions) {
        if (callbacks::handlers[action].size() != 0) {
            callbacks::handlers[action][0](event);
        }
    }
    else
    {
        auto it = handlers.find(action);
        if (it == handlers.end()) return;

        for (auto handler : it->second) {
            handler(event);
        }
    }
}
