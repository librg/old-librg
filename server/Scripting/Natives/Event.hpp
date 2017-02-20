#ifndef __event_system
#define __event_system

using namespace Sqrat;

namespace Server    {
namespace Scripting {


namespace Event
{
    static std::unordered_map<std::string, std::vector<Function>> eventHandlers;

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
                handler.Execute(params);
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
