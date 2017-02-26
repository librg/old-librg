#ifndef __event_manager
#define __event_manager

#include <uv.h>

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

#include <Utils/Singleton.h>

namespace Server {
namespace Event {

typedef std::function<void(void*, void*)> callback_generic;

enum
{
    EventType_Generic,
    EventType_Script,
};

struct ListenerInfo
{
    callback_generic callback;
    void* blob;
};

struct DispatchData
{
    ListenerInfo info;
    void* event;
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
     * @param name  Event name under which the handler should be registered.
     * @param
     */
    void AddListener(std::string name, callback_generic callback, void* blob);

    /**
     * Public API method for triggering server event. This method passes handler arguments via JSON blob. This method calls all registered handlers under specified event name.
     * @param eventName   Name of the event to call.
     * @param params      JSON serialized data blob.
     */
    void Dispatch(std::string name, void* event);

private:
    static void Callback(uv_async_t* req);
    static void Cleanup(uv_async_t* req);

    void Add(std::string name, ListenerInfo info);

    std::unordered_map<std::string, std::vector<ListenerInfo>> mEventHandlers;
};

} // Event
} // Server

#endif
