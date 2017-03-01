#ifndef __event_manager
#define __event_manager

#include <uv.h>
#include <sqrat.h>

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

#include <Utils/Singleton.h>

using callback_generic = std::function<void(const void*, void*)>;
using callback_script = std::function<void(const void*, Sqrat::Function*)>;
using callback_response = std::function<void*(const void*, Sqrat::Array*)>;
using callback_array = std::function<Sqrat::Array*(HSQUIRRELVM vm)>;

#define EVENT_GENERIC(name) void name##(const void* data, void* blob)
#define EVENT_RESPONSE(name) void* name##(const void* data, Sqrat::Array* array)
#define EVENT_ARRAY(name) Sqrat::Array* name##(HSQUIRRELVM vm)

inline static void* GenericNoResponse(const void*, Sqrat::Array*) {
    return nullptr;
}

inline static Sqrat::Array* GenericNoArray(HSQUIRRELVM vm) {
    return nullptr;
}

#define EVENT_PARAM(data,cb) { data, nullptr, cb }
#define EVENT_PARAM_SQ(cb) { nullptr, nullptr, cb }
#define EVENT_PARAM_CPP(data) { data, nullptr, GenericNoArray }
#define EVENT_PARAM_SQ_INTERNAL(array) { nullptr, array, GenericNoArray }

struct ScriptEvent
{
    void* params;
    callback_script caller;
};

typedef ScriptEvent DispatchEvent;

struct DispatchParams
{
    void* event;
    Sqrat::Array* array;
    callback_array arproc;
};

namespace Server::Event {

struct ListenerInfo
{
    callback_generic callback;
    callback_response responder;
    void* blob;
};

struct DispatchData
{
    ListenerInfo info;
    void* event;
    Sqrat::Array* array;
};

struct DispatchCleanupStack
{
    void* event;
    Sqrat::Array* array;
};

class Manager : public Singleton<Manager>
{
    friend class Singleton<Manager>;

public:
    Manager() = default;
    ~Manager() = default;
    void Init();

    /**
     * Public API method for adding event handler. Multiple event handlers per event name are supported.
     * @param name      Event name under which the handler should be registered.
     * @param callback  Callback that would be executed.
     * @param blob      Internal data for the listener. (Optional)
     */
    size_t AddListener(std::string name, callback_generic callback, callback_response responder, void* blob=0);

    void RemoveListener(std::string name, size_t handlerId);

    /**
     * Public API method for triggering server event. This method passes custom event data to the callback. This method calls all registered handlers under specified event name.
     * @param eventName   Name of the event to call.
     * @param event       Event data to be passed.
     */
    void Dispatch(std::string name, DispatchParams params);

private:
    static void Callback(uv_async_t* req);
    static void Cleanup(uv_async_t* req);
    static void CleanupEvent(uv_async_t* req);

    std::unordered_map<std::string, std::vector<ListenerInfo>> mEventHandlers;
};

}

#endif
