// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/network.h>

using namespace librg;

void librg::network::set_sync_cb(librg::core::rgmode mode, librg::network::sync_callback_t callback)
{
    syncCallbacks[mode] = callback;
}
