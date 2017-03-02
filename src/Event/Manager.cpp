#include <librg/Event/Manager.h>

namespace Server {
namespace Event {

void Manager::Init() {
    // TODO(zaklaus): do something useful, if required..
}

size_t Manager::AddListener(std::string name, callback_generic callback, callback_response responder, void* blob) {
    ListenerInfo info{ callback, responder, blob };

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

void Manager::Dispatch(std::string name, DispatchParams params) {
    if(mEventHandlers.find(name) != mEventHandlers.end()) {
        for(auto handler : mEventHandlers[name]) {
            uv_async_t* async = new uv_async_t;

            if(!params.array && handler.blob) {
                params.array = params.arproc(((Sqrat::Function*)handler.blob)->GetVM());
            }

            auto data = new DispatchData{ handler, params.event, params.array };
            uv_async_init(uv_default_loop(), async, &Manager::Callback);
            async->data = (void*)data;
            uv_async_send(async);
        }
    }

    // NOTE(zaklaus): Destroy the event data once we're done with the calls.
    uv_async_t* async = new uv_async_t;
    uv_async_init(uv_default_loop(), async, &Manager::CleanupEvent);
    async->data = (void*)new DispatchCleanupStack{ params.event, params.array };
    uv_async_send(async);
}

void Manager::Callback(uv_async_t* req) {
    auto data = (DispatchData*)req->data;
    void* params = data->info.responder(data->event, data->array);

    data->info.callback(params, data->info.blob);

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
    auto data = (DispatchCleanupStack*)req->data;
    delete data->array;
    delete data->event;
    delete data;
    uv_close((uv_handle_t*)req, NULL);
}

} // Event
} // Server
