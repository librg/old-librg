// Copyright ReGuider Team, 2016-2017
//
#include <librg/callbacks.h>

using namespace librg;

std::unordered_map<uint64_t, std::vector<callbacks::callback_t>> callbacks::handlers;

void callbacks::set(callbacks::actions action, callbacks::callback_t callback)
{
    auto it = handlers.find(action);

    if (it != handlers.end()) {
        if (action < callbacks::num_of_actions && handlers[action].size() != 0) {
            handlers[action][0] = callback;
        }
        else {
            handlers[action].push_back(callback);
        }
    }
    else
    {
        std::vector<callback_t> handler = { callback };
        handlers[action] = handler;
    }
}
