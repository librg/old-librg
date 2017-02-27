#include "Manager.h"

namespace Server {
namespace Event {

void Manager::Init() {
    // TODO(zaklaus): do something useful, if required..
}

size_t Manager::AddListener(std::string name, callback_generic callback, void* blob) {
    ListenerInfo info{ callback, blob };

    if(mEventHandlers.find(name) != mEventHandlers.end()) {
        mEventHandlers[name].push_back(info);
    } else {
        std::vector<ListenerInfo> newList = { info };
        mEventHandlers.insert(std::make_pair(name, newList));
    }

    return mEventHandlers[name].size() - 1;
}

void Manager::RemoveListener(std::string name, size_t handlerId) {
    if(mEventHandlers.find(name) != mEventHandlers.end()) {
        try {
            mEventHandlers[name].erase(mEventHandlers[name].begin()+handlerId);
        } catch(std::exception ex) {
            // TODO(zaklaus): Print error message here!
        }
    }
}

void Manager::ReplaceListener(std::string name, size_t handlerId, callback_generic callback, void* blob) {
    ListenerInfo info{ callback, blob };

    if(mEventHandlers.find(name) != mEventHandlers.end()) {
        try {
            mEventHandlers[name][handlerId] = info;
        } catch(std::exception ex) {
            // TODO(zaklaus): Print error message here!
        }
    }
}

size_t Manager::UpdateListener(std::string name, size_t handlerId, callback_generic callback, void* blob) {
    ListenerInfo info{ callback, blob };
    bool isPushed = true;

    if(mEventHandlers.find(name) != mEventHandlers.end()) {
        try {
            mEventHandlers[name][handlerId] = info;
            isPushed = false;
        } catch(std::exception ex) {
            mEventHandlers[name].push_back(info);
        }
    } else {
        std::vector<ListenerInfo> newList = { info };
        mEventHandlers.insert(std::make_pair(name, newList));
    }

    return isPushed ? mEventHandlers[name].size() - 1 : handlerId;
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

    // NOTE(zaklaus): Destroy the event data once we're done with the calls.
    uv_async_t* async = new uv_async_t;
    uv_async_init(uv_default_loop(), async, &Manager::CleanupEvent);
    async->data = event;
    uv_async_send(async);
}

void Manager::Callback(uv_async_t* req) {
    auto data = (DispatchData*)req->data;

    data->info.callback(data->event, data->info.blob);

    uv_async_t* async = new uv_async_t;
    uv_async_init(uv_default_loop(), async, &Manager::Cleanup);

    async->data = req->data;
    uv_close((uv_handle_t*)req, NULL);

    uv_async_send(async);
}

void Manager::Cleanup(uv_async_t* req) {
    delete req->data;
    uv_close((uv_handle_t*)req, NULL);
}

void Manager::CleanupEvent(uv_async_t* req) {
    delete req->data;
    uv_close((uv_handle_t*)req, NULL);
}

} // Event
} // Server
