// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>

void librg::network::add(int messageId, librg::network::callback_t callback)
{
    handlers[messageId] = callback;
}