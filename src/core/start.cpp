// Copyright ReGuider Team, 2016-2017
//
#include <uv.h>

#include <librg/core.h>
#include <librg/network.h>

using namespace librg;

void core::start(std::string ip, int port)
{
    if (core::is_server()) {
        network::server(port);
    }
    else {
        network::client(ip, port);
    }

    // starting loop
    uv_run(uv_default_loop(), core::is_manual() ? UV_RUN_NOWAIT : UV_RUN_DEFAULT);
}
