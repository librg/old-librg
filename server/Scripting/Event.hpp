#ifndef __event_system
#define __event_system

using namespace Sqrat;

namespace Server    {
namespace Scripting {


namespace Event
{
    static std::unordered_map<std::string, Function> eventHandlers;

    inline static void eventAddHandler(const char* handlerName, Function callback)
    {
        eventHandlers.insert(std::make_pair(std::string(handlerName), callback));
    }

    inline static void eventServerTrigger(const char* handlerName, const char* params)
    {
        if(eventHandlers.find(handlerName) != eventHandlers.end())
        {
            eventHandlers[handlerName].Execute(params);
        }
    }

    inline static void Install(Table& table)
    {
        table.Func("eventAddHandler",    &eventAddHandler);
        table.Func("eventServerTrigger", &eventServerTrigger);
    }
}



}
}

#endif // __event_system
