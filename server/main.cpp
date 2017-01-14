#include "stdinc.h"

int64_t counter = 0;
char buffer[1024];

/**
 * Main loop ticker
 * @param handle [description]
 */
void timed_loop(uv_timer_t* handle)
{
    MOServer::Core::Instance()->Tick(counter++);
}

/**
 * Main loop ticker
 * @param handle [description]
 */
void idle_loop(uv_idle_t* handle)
{
    MOServer::Core::Instance()->Idle();
}


/**
 * System signal hanlder
 * @param req
 * @param signum
 */
void signal_handler(uv_signal_t *req, int signum)
{
    // stop for ctrl+C
    if (signum == 2) {
        printf("Exiting!\n");
        uv_stop(uv_default_loop());
    }

    uv_signal_stop(req);
}

/**
 * TODO(inlife): make input handling
 * @param req
 */
void on_type(uv_fs_t *req) {
    printf("onconsole %s\n", buffer);
    buffer[0] = 0;
}

/**
 * Main program enter point
 * @param  argc
 * @param  argv
 * @return exit code
 */
int main(int argc, char * argv[]) {
    uv_idle_t idler;
    uv_timer_t timer_req;
    uv_fs_t stdin_watcher;

    HSQUIRRELVM v;
    v = sq_open(1024); //creates a VM with initial stack size 1024

    //do some stuff with squirrel here

    sq_close(v);

    // create and initialize
    MOServer::Core* core = new MOServer::Core();

    // define main timed loop (network send)
    // start after 1 sec, each 15 ms
    uv_timer_init(uv_default_loop(), &timer_req);
    uv_timer_start(&timer_req, timed_loop, 1000, 15);

    // define main idle loop (network receieve)
    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, idle_loop);

    // singal handling
    uv_signal_t sig;
    uv_signal_init(uv_default_loop(), &sig);
    uv_signal_start(&sig, signal_handler, SIGINT);

    // input handling
    // uv_buf_t buf = uv_buf_init(buffer, 1024);
    // uv_fs_read(uv_default_loop(), &stdin_watcher, 0, &buf, 1, -1, on_type);

    // starting loop
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    // after work is done, closing loop
    uv_loop_close(uv_default_loop());

    delete core;
    return 0;
}
