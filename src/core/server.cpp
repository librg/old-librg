#include <librg/core/server.h>

using namespace librg::core;

int width, height;

/**
 * Main loop ticker
 * @param handle [description]
 */
void timed_loop(uv_timer_t* handle)
{
    librg::core::tick();
}

/**
 * Main loop ticker
 * @param handle [description]
 */
void idle_loop(uv_timer_t* handle)
{
    librg::core::poll();
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
void on_console_message(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf)
{
    buf->base[nread] = '\0';
    // librg::core::onInput(buf->base);
}

void update(uv_timer_t* req)
{
    char data[500];

    uv_write_t write_req;
    uv_buf_t buf;
    buf.base = data;
    buf.len = sprintf(data, "\0337\033[H\033[47;37m\033[2K\033[30m  Hello world\033[0;%dHTesting stuff\0338\033[39;49m", width - 20);
    uv_write(&write_req, (uv_stream_t*)req->data, &buf, 1, NULL);
}

/**
 * Starts the server!
 * @param  argc
 * @param  argv
 * @return exit code
 */
int librg::core::server(int argc, char * argv[])
{
    uv_timer_t idler;
    uv_timer_t timer_req;
    uv_tty_t tty;

#ifdef WIN32
    // Set our locale to the C locale, as Unicode output only functions in this locale
    std::setlocale(LC_ALL, "C");
    SetConsoleOutputCP(CP_UTF8);
#endif
    // Server::Core::Log("\033[2J\033[H\033[1B\033[1C\033[42;37m%s");


    // define main timed loop (network send)
    // start after 1 sec, each 15 ms
    uv_timer_init(uv_default_loop(), &timer_req);
    uv_timer_start(&timer_req, timed_loop, 250, 16);

    uv_timer_init(uv_default_loop(), &idler);
    uv_timer_start(&idler, idle_loop, 0, 1);

    // define main idle loop (network receieve)
    // uv_idle_init(uv_default_loop(), &idler);
    // uv_idle_start(&idler, idle_loop);

    // singal handling
    uv_signal_t sig;
    uv_signal_init(uv_default_loop(), &sig);
    uv_signal_start(&sig, signal_handler, SIGINT);

    // terminal window
    uv_tty_init(uv_default_loop(), &tty, 0, 1);
    uv_tty_set_mode(&tty, UV_TTY_MODE_NORMAL);

    // uv_timer_t tick;
    // tick.data = &tty;
    // fprintf(stderr, "Width %d, height %d\n", width, height);
    // uv_timer_init(uv_default_loop(), &tick);
    // uv_timer_start(&tick, update, 200, 200);

    // setup reading callback
    uv_read_start((uv_stream_t*)&tty, tty_alloc, on_console_message);

    if (uv_tty_get_winsize(&tty, &width, &height)) {
        fprintf(stderr, "Could not get TTY information\n");
        // uv_tty_reset_mode();
    }

    // starting loop
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    // after work is done, closing loop
    uv_loop_close(uv_default_loop());
    uv_tty_reset_mode();

    return 0;
}


// void event_system_cpp_to_sq() {
//     int amount = 666;
//     std::string name = "Vlad";

//     Event::Manager::Instance()->Dispatch("onDeveloperDrinksVodka", EVENT_PARAM_SQ([=](HSQUIRRELVM vm){
//         auto array = new Sqrat::Array(vm);
//         array->Append(amount);
//         array->Append(name);
//         return array;
//     }));
// }

// // TODO(zaklaus): Move these test blocks somewhere, main.cpp just gets bloated by this.
// struct VodkaEvent
// {
//     std::string amount;
// };

// void* VodkaEventResponse(const void* data, Sqrat::Array* array) {
//     if(array!=0) {
//         auto vodka = new VodkaEvent;
//         std::string amount = array->Pop().Cast<char*>();
//         vodka->amount = amount;
//         return vodka;
//     }
//     return (void*)data;
// }

// void event_system_test() {
//     size_t handlerId = Event::Manager::Instance()->AddListener("onVodkaTooWeak", [](const void* event, void* /* blob */){
//         const VodkaEvent* vodka = (VodkaEvent*)event;
//         Core::Log("We need %s of vodka!", vodka->amount.c_str());
//     }, VodkaEventResponse);

//     Event::Manager::Instance()->Dispatch("onVodkaTooWeak", EVENT_PARAM_CPP(new VodkaEvent{ "a lot" }));

//     Event::Manager::Instance()->AddListener("onTestMessageRequested", [](const void* /* event */, void* /* blob */){
//         Core::Log("This is a test message!");
//     }, GenericNoResponse);
// }

// event_system_test();




/*
Async stuff

// void async_cb(uv_async_t* async) {
//     printf("async_cb %d\n", *((int*) async->data));
//     uv_close((uv_handle_t*) async, NULL);
// }


    // // async test
    // int a = 5;

    // uv_async_t async;
    // uv_async_init(uv_default_loop(), &async, async_cb);
    // async.data = &a;
    // uv_async_send(&async);

    // int b = 6;

    // uv_async_t async2;
    // uv_async_init(uv_default_loop(), &async2, async_cb);
    // async2.data = &b;
    // uv_async_send(&async2);

*/


/*
Squirrel stuff


    // HSQUIRRELVM v;
    // v = sq_open(1024); //creates a VM with initial stack size 1024

    // //do some stuff with squirrel here

    // sq_close(v);


*/


/*
BEAUTUFL TTY
 */
// uv_loop_t *loop;
// uv_tty_t tty;
// uv_timer_t tick;
// uv_write_t write_req;
// int width, height;
// int pos = 0;
// char *message = "  Hello TTY  ";


// void update(uv_timer_t *req)
// {
//     char data[500];

//     uv_buf_t buf;
//     buf.base = data;
//     buf.len = sprintf(data, "\033[2J\033[H\033[%dB\033[%luC\033[42;37m%s",
//                             pos,
//                             (unsigned long) (width-strlen(message))/2,
//                             message);

//     uv_write(&write_req, (uv_stream_t*) &tty, &buf, 1, NULL);

//     pos++;
//     if (pos > height) {
//         uv_tty_reset_mode();
//         uv_timer_stop(&tick);
//     }
// }


// int main() {
//     loop = uv_default_loop();

//     uv_tty_init(loop, &tty, 1, 0);
//     uv_tty_set_mode(&tty, 0);

//     if (uv_tty_get_winsize(&tty, &width, &height)) {
//         fprintf(stderr, "Could not get TTY information\n");
//         uv_tty_reset_mode();
//         return 1;
//     }

//     fprintf(stderr, "Width %d, height %d\n", width, height);
//     uv_timer_init(loop, &tick);
//     uv_timer_start(&tick, update, 200, 200);
//     return uv_run(loop, UV_RUN_DEFAULT);
// }