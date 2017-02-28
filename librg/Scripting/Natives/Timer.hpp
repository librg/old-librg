#ifndef __scripting_timer
#define __scripting_timer

#include <uv.h>
#include <cstdint>

namespace Server    {
namespace Scripting {


namespace Timer
{
    /**
     * Private method for cleaning up timers(intervals)
     * after they are finished
     * @param req
     */
    inline static void private_cleanup(uv_async_t* req)
    {
        delete (Sqrat::Function*)req->data;
        uv_close((uv_handle_t*) req, NULL);
    }

    /**
     * Private method for calling up callback
     * when interval iterations is triggered
     * @param req
     */
    inline static void private_intervalCallback(uv_timer_t* req)
    {
        ((Sqrat::Function*)req->data)->Execute();
    }

    /**
     * Public api method, for creating ticking timer with provided interval
     * @param  callback    Squirrel wrapped function object, which will be added as a handler
     * @param  miliseconds delay between each tick
     * @return pointer onto created timer casted to uint
     */
    inline static std::uintptr_t setInterval(Sqrat::Function callback, uint16_t miliseconds)
    {
        uv_timer_t* timer_req = new uv_timer_t;
        timer_req->data = new Sqrat::Function(callback);

        uv_timer_init(uv_default_loop(), timer_req);
        uv_timer_start(timer_req, private_intervalCallback, miliseconds, miliseconds);

        return reinterpret_cast<std::uintptr_t>(timer_req);
    }

    /**
     * Public api method for cleaning up created timer
     * @param req uint pointer, which was returned with setInterval
     */
    inline static void clearInterval(std::uintptr_t req)
    {
        uv_timer_t* timer_req = reinterpret_cast<uv_timer_t*>(req);
        uv_timer_stop(timer_req);
        uv_async_t* async = new uv_async_t;
        uv_async_init(uv_default_loop(), async, private_cleanup);
        async->data = timer_req->data;
        uv_async_send(async);
    }

    /**
     * Registry method
     * @param native
     */
    inline static void Install(Sqrat::Table& native)
    {
        native.Func("setInterval",   &setInterval);
        native.Func("clearInterval", &clearInterval);
    }
}



} // Scripting
} // Server

#endif // __scripting_timer
