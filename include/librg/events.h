#ifndef events_h
#define events_h

#include <map>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

#include <uv.h>
#include <sqrat.h>

namespace librg
{
    void events_initialize();
    static inline void events_terminate() {};

    namespace events
    {
        inline static void* GenericNoProxy(const void*, Sqrat::Array*) {
            return nullptr;
        }

        inline static void GenericNoArray(Sqrat::Array *array) { }


        #define EVENT_GENERIC(name)     void name##(const void* data, void* blob)
        #define EVENT_RESPONSE(name)    void* name##(const void* data, Sqrat::Array* array)
        #define EVENT_ARRAY(name)       Sqrat::Array* name##(HSQUIRRELVM vm)

        #define EVENT_PARAM(data,cb)    { data, nullptr, cb }
        #define EVENT_PARAM_SQ(cb)      { nullptr, nullptr, cb }
        #define EVENT_PARAM_CPP(data)   { data, nullptr, librg::events::GenericNoArray }
        #define EVENT_PARAM_SQ_INTERNAL(array) { nullptr, array, librg::events::GenericNoArray }

        using callback_generic  = std::function<void(const void*, void*)>;
        using callback_script   = std::function<void(const void*, Sqrat::Function*)>;
        using callback_proxy = std::function<void*(const void*, Sqrat::Array*)>;
        using callback_array    = std::function<void(Sqrat::Array *array)>;


        struct script_event_t {
            void *params;
            callback_script caller;
        };

        typedef script_event_t dispatch_event_t;

        struct dispatch_params_t {
            void *event;
            Sqrat::Array *array;
            callback_array arproc;
        };

        struct listener_info_t {
            callback_generic callback;
            callback_proxy responder;
            void* blob;
        };

        struct dispatch_data_t {
            listener_info_t info;
            void* event;
            Sqrat::Array* array;
        };

        struct dispatch_cleanup_stack_t {
            void* event;
            Sqrat::Array* array;
        };

        extern std::unordered_map<std::string, std::vector<listener_info_t>> _events;


        /**
         * Public API method for adding event handler.
         * Multiple event handlers per event name are supported.
         *
         * @param name      Event name under which the handler should be registered.
         * @param callback  Callback that would be executed.
         * @param blob      Internal data for the listener. (Optional)
         */
        size_t add(std::string name, callback_generic callback, callback_proxy proxy, void *blob = nullptr);

        /**
         * Public API method for triggering server event.
         * This method passes custom event data to the callback.
         * This method calls all registered handlers under specified event name.
         *
         * @param eventName   Name of the event to call.
         * @param event       Event data to be passed.
         */
        void trigger(std::string name, dispatch_params_t params);

        /**
         * [remove description]
         * @param  name      [description]
         * @param  handlerId [description]
         * @return           [description]
         */
        bool remove(std::string name, size_t handler);
    }
}

#endif // events_h
