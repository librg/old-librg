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

    /**
     * Public API method for adding event handler. Multiple event handlers per event name are supported.
     * @param eventName Event name under which the handler should be registered.
     * @param callback    Squirrel wrapped function object.
     */
    inline static void eventAddHandler(const char* eventName, Function callback)
    {
        if(eventHandlers.find(eventName) != eventHandlers.end())
        {
            eventHandlers[eventName].push_back(callback);
        }
        else
        {
            std::vector<Function> newList = { callback };
            eventHandlers.insert(std::make_pair(std::string(eventName), newList));
        }
    }

    /**
     * Public API method for triggering server event. This method passes handler arguments via JSON blob. This method calls all registered handlers under specified event name.
     * @param eventName   Name of the event to call.
     * @param params      JSON serialized data blob.
     */
    inline static void eventServerTrigger(const char* eventName, const char* params)
    {
        if(eventHandlers.find(eventName) != eventHandlers.end())
        {
            for(auto handler : eventHandlers[eventName])
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

    /**
     * Registry method
     * @param table
     */
    inline static void Install(Table& table)
    {
        table.Func("eventAddHandler",    &eventAddHandler);
        table.Func("eventServerTrigger", &eventServerTrigger);
    }
}



} // Scripting
} // Server

#endif // __event_system
