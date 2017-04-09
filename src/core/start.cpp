// Copyright ReGuider Team, 2016-2017
//
#include <uv.h>

#include <librg/core.h>
#include <librg/network.h>
#include <librg/streamer.h>

using namespace librg;

void core::start(config_t config)
{
    if (core::is_server()) {
        if (HMM_LengthVec3(config.worldSize) != 0.f) {
            streamer::clear(aabb_t(config.worldSize));
        }

        network::server(config.port);
    }
    else {
        network::client(config.ip, config.port);
    }

    // starting loop
    uv_run(uv_default_loop(), core::is_manual() ? UV_RUN_NOWAIT : UV_RUN_DEFAULT);
}
