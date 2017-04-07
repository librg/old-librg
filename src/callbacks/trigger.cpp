// Copyright ReGuider Team, 2016-2017
//
#include <librg/callbacks.h>

using namespace librg;

void callbacks::trigger(callbacks::actions action, callbacks::evt_t* event)
{
    if (callbacks::handlers[action]) {
        callbacks::handlers[action](event);
    }
}
