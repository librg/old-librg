// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>
#include <librg/core/shared.h>

#include <librg/network/server/connection.hpp>
#include <librg/network/client/connection.hpp>
#include <librg/network/client/streaming.hpp>
#include <librg/network/server/streaming.hpp>

using namespace librg;

void librg::network::set_sync_cb(librg::core::rgmode mode, librg::network::sync_callback_t callback)
{
    syncCallbacks[mode] = callback;
}
