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

#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

int main() {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    printf("Now quitting.\n");
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);
    return 0;
}
