#ifndef __event_system
#define __event_system

using namespace Sqrat;

namespace Server    {
namespace Scripting {


namespace Event
{
    struct ScriptEvent
    {
        std::string params;
    };

    /**
     * Public API method for adding event handler. Multiple event handlers per event name are supported.
     * @param eventName Event name under which the handler should be registered.
     * @param callback    Squirrel wrapped function object.
     */
    inline static void eventAddHandler(const char* eventName, Function callback)
    {
        Server::Event::Manager::Instance()->AddListener(eventName, [](void *event, void* blob){
            auto script = (ScriptEvent*)event;
            printf("Some message here: %s\n\n", script->params.c_str());
            auto cb = (Function*)blob;
            cb->Execute(script->params);
        }, new Function(callback));
    }

    /**
     * Public API method for triggering server event. This method passes handler arguments via JSON blob. This method calls all registered handlers under specified event name.
     * @param eventName   Name of the event to call.
     * @param params      JSON serialized data blob.
     */
    inline static void eventServerTrigger(const char* eventName, const char* params)
    {
        Server::Event::Manager::Instance()->Dispatch(eventName,
            new ScriptEvent{ params }
        );
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
