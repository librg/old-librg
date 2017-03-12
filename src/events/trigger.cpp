#include <librg/events.h>

using namespace librg::events;

/**
 * Private inner file
 */
void _cleanup(uv_async_t* req) {
    delete req->data;
    uv_close((uv_handle_t*)req, NULL);
}

/**
 * Private inner file
 */
void _callback(uv_async_t* req)
{
    auto data    = (dispatch_data_t *)req->data;
    void *params = data->info.responder(data->event, data->array);

    data->info.callback(params, data->info.blob);

    uv_async_t* async = new uv_async_t;
    uv_async_init(uv_default_loop(), async, _cleanup);

    async->data = req->data;
    uv_close((uv_handle_t*)req, NULL);

    uv_async_send(async);
}

/**
 * Private inner file
 */
void _cleanup_event(uv_async_t* req)
{
    auto data = (dispatch_cleanup_stack_t *)req->data;

    delete data->array;
    delete data->event;
    delete data;

    uv_close((uv_handle_t*)req, NULL);
}

void librg::events::trigger(std::string name, dispatch_params_t params)
{
    if (_events.find(name) != _events.end()) {
        for (auto handler : _events[name]) {
            uv_async_t* async = new uv_async_t;

            // NOTE:
            // happens only if its a sq listener
            // and its called from cpp side
            if (!params.array && handler.blob) {
                // trigger callback to create sq function parameter (array)
                params.array = params.arproc(((Sqrat::Function*)handler.blob)->GetVM());
            }

            auto data = new dispatch_data_t { handler, params.event, params.array };

            uv_async_init(uv_default_loop(), async, _callback);
            async->data = (void*)data;
            uv_async_send(async);
        }
    }

    // NOTE(zaklaus): Destroy the event data once we're done with the calls.
    uv_async_t* async = new uv_async_t;
    uv_async_init(uv_default_loop(), async, _cleanup_event);
    async->data = (void *)new dispatch_cleanup_stack_t{ params.event, params.array };
    uv_async_send(async);
}
