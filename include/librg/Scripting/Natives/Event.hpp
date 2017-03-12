#ifndef __scripting_event
#define __scripting_event

using namespace Sqrat;

namespace librg
{
    namespace scripting
    {
        namespace event
        {
            /**
             * Public API method for adding event listener. Multiple event handlers per event name are supported.
             * @param eventName Event name under which the listener should be registered.
             * @param callback    Squirrel wrapped function object.
             */
            inline static void eventAddListener(const char* eventName, Function callback)
            {
                size_t handlerId = Server::Event::Manager::Instance()->AddListener(eventName, [](const void *event, void* blob){
                    auto array = (Sqrat::Array*)event;
                    auto cb = (Function*)blob;
                    cb->Execute(*array);
                }, [](const void* data, Sqrat::Array* array){
                    return array ? (void*)array : (void*)data;
                }, new Function(callback));
            }

            /**
             * Public API method for dispatching an event. This method passes handler arguments via Squirrel array. This method calls all registered handlers under specified event name.
             * @param eventName   Name of the event to call.
             * @param params      Array of values.
             */
            inline static void eventDispatch(const char* eventName, Array array)
            {
                Server::Event::Manager::Instance()->Dispatch(eventName, EVENT_PARAM_SQ_INTERNAL(new Array(array)));
            }

            /**
             * Registry method
             * @param table
             */
            inline static void install(Table& table)
            {
                table.Func("eventAddListener",    &eventAddListener);
                table.Func("eventDispatch", &eventDispatch);
            }
        }
    }
}

#endif // __scripting_event
