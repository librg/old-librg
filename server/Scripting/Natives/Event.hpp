#ifndef __event_system
#define __event_system

using namespace Sqrat;
#include "Core.h"


namespace Server    {
namespace Scripting {

namespace Event
{

    /**
     * Public API method for adding event handler. Multiple event handlers per event name are supported.
     * @param eventName Event name under which the handler should be registered.
     * @param callback    Squirrel wrapped function object.
     */
    inline static void eventAddHandler(const char* eventName, Function callback)
    {
        size_t handlerId = Server::Event::Manager::Instance()->AddListener(eventName, [](const void *event, void* blob){
            auto script = (ScriptEvent*)event;
            auto cb = (Function*)blob;
            script->caller(script->params, cb);
        }, [](const void* data, Sqrat::Array* array){
            if(array) {
                return (void*)-1;
            }
            return (void*)data;
        }, new Function(callback));
    }

    /**
     * Public API method for triggering server event. This method passes handler arguments via JSON blob. This method calls all registered handlers under specified event name.
     * @param eventName   Name of the event to call.
     * @param params      JSON serialized data blob.
     */
    inline static void eventServerTrigger(const char* eventName, Array array)
    {
        Server::Event::Manager::Instance()->Dispatch(eventName, NULL, new Array(array));
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
