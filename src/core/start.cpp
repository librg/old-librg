// Copyright ReGuider Team, 2016-2017
//
#include <uv.h>

#include <librg/core.h>
#include <librg/network.h>
#include <librg/streamer.h>
#include <librg/events.h>
#include <librg/utils/timing.hpp>

using namespace librg;

uv_timer_t librg_tick_loop;
double librg_last_ticktime;

/**
* Main tick method
*/
void on_tick_loop(uv_timer_t* req)
{
    double newtime = get_time();
    events::trigger(events::on_tick, new events::event_tick_t{0, newtime - librg_last_ticktime});
    librg_last_ticktime = newtime;

    streamer::update();
}

void core::start(config_t config)
{
    if (!core::is_manual()) {
        network::start(config);
    }

    // setup default value for tickrate
    if (!config.tick_delay || config.tick_delay < 16) {
        config.tick_delay = 16;
    }

    uv_timer_init(uv_default_loop(), &librg_tick_loop);
    uv_timer_start(&librg_tick_loop, on_tick_loop, 250, config.tick_delay);

    events::trigger(events::on_start, nullptr);

    // starting loop
    uv_run(uv_default_loop(), core::is_manual() ? UV_RUN_NOWAIT : UV_RUN_DEFAULT);
}
