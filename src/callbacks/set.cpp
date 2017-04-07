// Copyright ReGuider Team, 2016-2017
//
#include <librg/callbacks.h>

using namespace librg;

std::array<callbacks::callback_t, NATIVE_CALLBACKS> callbacks::handlers;

void callbacks::set(callbacks::actions action, callbacks::callback_t callback)
{
    callbacks::handlers[action] = callback;
}
