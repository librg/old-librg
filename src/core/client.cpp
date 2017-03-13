#include <librg/core/client.h>

using namespace librg;

bool initialized = false;

uv_timer_t* idler;
uv_timer_t* timer_req;

/**
 * Main loop ticker
 * @param handle [description]
 */
void c_timed_loop(uv_timer_t* handle)
{
    core::tick();
}

/**
 * Main loop ticker
 * @param handle [description]
 */
void c_idle_loop(uv_timer_t* handle)
{
    core::poll();
}


void c_initialize()
{
    auto idler = new uv_timer_t;
    auto timer_req = new uv_timer_t;

    // define main timed loop (network send)
    // start after 1 sec, each 15 ms
    uv_timer_init(uv_default_loop(), timer_req);
    uv_timer_start(timer_req, c_timed_loop, 250, 16);

    uv_timer_init(uv_default_loop(), idler);
    uv_timer_start(idler, c_idle_loop, 0, 1);
}

void core::client_terminate()
{
    delete idler;
    delete timer_req;
}

void core::client_tick(uv_loop_t* loop)
{
    if (!loop) {
        loop = uv_default_loop();
    }

    if (!initialized) {
        c_initialize();
    }

    // run libuv one-time iteration
    uv_run(loop, UV_RUN_NOWAIT);
}

void core::client(int argc, char * argv[])
{

}
