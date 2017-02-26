#include "Manager.h"

namespace Server {
namespace Event {

void Manager::Init() {
    // TODO(zaklaus): do something useful, if required..
}

void Manager::AddListener(std::string name, callback_generic callback, void* blob) {
    ListenerInfo info{ callback, blob };

    if(mEventHandlers.find(name) != mEventHandlers.end()) {
        mEventHandlers[name].push_back(info);
    } else {
        std::vector<ListenerInfo> newList = { info };
        mEventHandlers.insert(std::make_pair(name, newList));
    }
}

void Manager::Dispatch(std::string name, void* event) {
    if(mEventHandlers.find(name) != mEventHandlers.end()) {
        for(auto handler : mEventHandlers[name]) {
            uv_async_t* async = new uv_async_t;
            auto data = new DispatchData{ handler, event };
            uv_async_init(uv_default_loop(), async, &Manager::Callback);
            async->data = (void*)data;
            uv_async_send(async);
        }
    }
}

void Manager::Callback(uv_async_t* req) {
    auto data = (DispatchData*)req->data;

    data->info.callback(data->event, data->info.blob);

    uv_async_t* async = new uv_async_t;
    uv_async_init(uv_default_loop(), async, &Manager::Cleanup);

    async->data = req->data;
    uv_async_send(async);
}

void Manager::Cleanup(uv_async_t* req) {
    auto data = (DispatchData*)req->data;
    delete data;
    uv_close((uv_handle_t*)req, NULL);
}

} // Event
} // Server
