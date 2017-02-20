#ifndef __event_system
#define __event_system

using namespace Sqrat;

namespace Server    {
namespace Scripting {


namespace Event
{
    struct EventData
    {
        Function* callback;
        std::string params;
    };

    static std::unordered_map<std::string, std::vector<Function>> eventHandlers;

    inline static void private_eventCleanup(uv_async_t* req)
    {
        auto data = (EventData*)req->data;
        delete data->callback;
        delete data;
        uv_close((uv_handle_t*)req, NULL);
    }

    inline static void private_eventCallback(uv_async_t* req)
    {
        auto data = (EventData*)req->data;
        data->callback->Execute(data->params);

        uv_async_t* async = new uv_async_t;
        uv_async_init(uv_default_loop(), async, private_eventCleanup);

        async->data = req->data;
        uv_async_send(async);
    }

    inline static void eventAddHandler(const char* handlerName, Function callback)
    {
        if(eventHandlers.find(handlerName) != eventHandlers.end())
        {
            eventHandlers[handlerName].push_back(callback);
        }
        else
        {
            std::vector<Function> newList = { callback };
            eventHandlers.insert(std::make_pair(std::string(handlerName), newList));
        }
    }

    inline static void eventServerTrigger(const char* handlerName, const char* params)
    {
        if(eventHandlers.find(handlerName) != eventHandlers.end())
        {
            for(auto handler : eventHandlers[handlerName])
            {
                uv_async_t* async = new uv_async_t;
                auto callback = new Function(handler);
                std::string cparams = params;
                auto data = new EventData { callback, cparams };
                uv_async_init(uv_default_loop(), async, private_eventCallback);
                async->data = (void*)data;
                uv_async_send(async);
            }
        }
    }

    inline static void Install(Table& table)
    {
        table.Func("eventAddHandler",    &eventAddHandler);
        table.Func("eventServerTrigger", &eventServerTrigger);
    }
}



} // Scripting
} // Server

#endif // __event_system
