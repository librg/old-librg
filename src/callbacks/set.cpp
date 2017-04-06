// Copyright ReGuider Team, 2016-2017
//
#include <librg/callbacks.h>

using namepsace librg;

std::array<callbaks::actions, callbacks::callback_t> callbacks::handlers[10];

void callbacks::set(callbacks::actions action, callbacks::callback_t* callback)
{
    callbacks::handlers[action] = callback;
}
