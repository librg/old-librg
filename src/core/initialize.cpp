// Copyright ReGuider Team, 2016-2017
//
#include <uv.h>

#define HANDMADE_MATH_IMPLEMENTATION
#include <librg/utils/linmath.h>

#include <librg/timing.hpp>

#ifdef WIN32
#include <clocale>
#endif

#include <librg/core.h>
#include <librg/callbacks.h>
#include <librg/entities.h>
#include <librg/network.h>
#include <librg/resources.h>
#include <librg/streamer.h>

using namespace librg;

uv_timer_t librg_poll_loop;
uv_tty_t librg_tty;

double librg_lasttime;

/**
 * Main polling method
 */
void on_poll_loop(uv_timer_t* req)
{
    network::poll();

    if (core::is_client()) {
        double newtime = get_time();
        // there goes calculated delta time per tick
        // librg::network::interpolate((newtime - librg_lasttime)*100.0);
        librg_lasttime = newtime;
    }
}

/**
 * System signal hanlder
 * @param req
 * @param signum
 */
void on_signal(uv_signal_t *req, int signum)
{
    // stop for ctrl+C
    if (signum == 2) {
        // Server::Core::Log("\nExiting!");
        uv_stop(uv_default_loop());
    }

    uv_signal_stop(req);
}

/**
 * Alloc callback for allocating input memory
 * @param handle         tty handle
 * @param suggested_size suggensted size by uv (65536 in most cases)
 * @param buf            buffer, where data will be written to, and read from by us
 */
static void tty_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
    buf->base = new char[1024];
    buf->len = 1024;
}

/**
 * On user console message
 * @param stream tty handle
 * @param nread  size of string
 * @param buf    buffer with data
 */
void on_console(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf)
{
    buf->base[nread] = '\0';
    // librg::core::onInput(buf->base);
    // add console event
    core::log(buf->base);
}

void librg::core_initialize(librg::mode_t mode)
{
    librg::core::set_mode(mode);

    librg::entities_initialize();
    librg::network_initialize();
    librg::resources_initialize();
    librg::streamer_initialize();

#ifdef WIN32
    // set our locale to the C locale
    // as unicode output only functions in this locale
    std::setlocale(LC_ALL, "C");
    SetConsoleOutputCP(CP_UTF8);
#endif

    // start loops
    uv_timer_init(uv_default_loop(), &librg_poll_loop);
    uv_timer_start(&librg_poll_loop, on_poll_loop, 0, 1);

    // singal handling
    // uv_signal_t sig;
    // uv_signal_init(uv_default_loop(), &sig);
    // uv_signal_start(&sig, on_signal, SIGINT);

    // terminal window
    uv_tty_init(uv_default_loop(), &librg_tty, 0, 1);
    uv_tty_set_mode(&librg_tty, UV_TTY_MODE_NORMAL);

    // setup reading callback
    uv_read_start((uv_stream_t*)&librg_tty, tty_alloc, on_console);

    // if (uv_tty_get_winsize(&tty, &width, &height)) {
    //     fprintf(stderr, "Could not get TTY information\n");
    //     // uv_tty_reset_mode();
    // }
}
