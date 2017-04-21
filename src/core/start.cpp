// Copyright ReGuider Team, 2016-2017
//
#include <uv.h>

#include <librg/core.h>
#include <librg/network.h>
#include <librg/streamer.h>
#include <librg/callbacks.h>
#include <librg/timing.hpp>

using namespace librg;

uv_timer_t librg_tick_loop;
double librg_last_ticktime;

/**
* Main tick method
*/
void on_tick_loop(uv_timer_t* req)
{
    // if (core::is_server()) {
    //     network::update();
    // }
    // TODO streamer::update();

    double newtime = get_time();
    callbacks::evt_tick_t tick_event = { 0, (newtime - librg_last_ticktime) };
    callbacks::trigger(callbacks::tick, (callbacks::evt_t*) &tick_event);
    librg_last_ticktime = newtime;
}

void core::start(config_t config)
{
    if (!core::is_manual()) {
        network::start(config);
    }

    uv_timer_init(uv_default_loop(), &librg_tick_loop);
    uv_timer_start(&librg_tick_loop, on_tick_loop, 250, config.tick_rate);

    auto event = callbacks::evt_start_t{};
    callbacks::trigger(callbacks::start, (callbacks::evt_t*)&event);

    // starting loop
    uv_run(uv_default_loop(), core::is_manual() ? UV_RUN_NOWAIT : UV_RUN_DEFAULT);
}
