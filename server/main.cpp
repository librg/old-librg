#include "stdinc.h"

// // 5ms
// const float TICK_INTEVAL = 0.005;

// int main(int argc, char * argv[])
// {
//     // create and initialize
//     MOEB::Server::Core* core = new MOEB::Server::Core();

//     // push and wait
//     while (core->IsRunning())
//     {
//         core->Tick();
//         sleep(TICK_INTEVAL);
//     }
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <uv.h>

// int main() {
//     uv_loop_t *loop = new uv_loop_t;// = malloc(sizeof(uv_loop_t));
//     uv_loop_init(loop);

//     printf("Now quitting.\n");
//     uv_run(loop, UV_RUN_DEFAULT);

//     uv_loop_close(loop);
//     // free(loop);
//     delete loop;
//     return 0;
// }

#include <stdio.h>
#include <uv.h>

int64_t counter = 0;

void main_loop(uv_idle_t* handle) {
    counter++;

    MOServer::Core::Instance()->Tick();

    if (counter >= 10e6)
        uv_idle_stop(handle);
}

int main() {
    uv_idle_t idler;

    // create and initialize
    MOServer::Core* core = new MOServer::Core();

    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, main_loop);

    printf("starting main loop...\n");
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    uv_loop_close(uv_default_loop());
    delete core;

    return 0;
}
