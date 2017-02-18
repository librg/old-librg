#ifndef __scripting_timer
#define __scripting_timer

#include <uv.h>
#include <cstdint>

using namespace Sqrat;

namespace Server    {
namespace Scripting {

namespace Timer
{
    inline static void private_cleanup(uv_async_t* req)
    {
        delete (Function*)req->data;
        uv_close((uv_handle_t*) req, NULL);
    }

    inline static void private_intervalCallback(uv_timer_t* req)
    {
        ((Function*)req->data)->Execute();
    }

    inline static  std::uintptr_t setInterval(Function callback, uint16_t miliseconds)
    {
        uv_timer_t* timer_req = new uv_timer_t;
        timer_req->data = new Function(callback);

        uv_timer_init(uv_default_loop(), timer_req);
        uv_timer_start(timer_req, private_intervalCallback, miliseconds, miliseconds);

        return reinterpret_cast<std::uintptr_t>(timer_req);
    }

    inline static void clearInterval(std::uintptr_t req)
    {
        uv_timer_t* timer_req = reinterpret_cast<uv_timer_t*>(req);
        uv_timer_stop(timer_req);
        uv_async_t* async = new uv_async_t;
        uv_async_init(uv_default_loop(), async, private_cleanup);
        async->data = timer_req->data;
        uv_async_send(async);
    }

    inline static void Install(HSQUIRRELVM vm)
    {
        // RootTable(vm).Func("setTimeout",    &setTimeout);
        RootTable(vm).Func("setInterval",   &setInterval);
        RootTable(vm).Func("clearInterval", &clearInterval);
    }
}



}
}

#endif // __scripting_timer
