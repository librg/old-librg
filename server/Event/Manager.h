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

typedef std::function<void(const void*, void*)> callback_generic;
typedef std::function<void(const void*, Sqrat::Function*)> callback_script;
typedef std::function<void*(const void*, Sqrat::Array*)> callback_response;

#define EVENT_GENERIC(name) void name##(const void* data, void* blob)
#define EVENT_RESPONSE(name) void* name##(const void* data, Sqrat::Array* array)

struct ScriptEvent
{
    void* params;
    callback_script caller;
};

typedef ScriptEvent DispatchEvent;

namespace Server {
namespace Event {

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
    void Dispatch(std::string name, void* event=0, Sqrat::Array* array=0);

private:
    static void Callback(uv_async_t* req);
    static void Cleanup(uv_async_t* req);
    static void CleanupEvent(uv_async_t* req);

    std::unordered_map<std::string, std::vector<ListenerInfo>> mEventHandlers;
};

} // Event
} // Server

#endif
