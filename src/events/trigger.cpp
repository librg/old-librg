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

void _trigger(std::unordered_map<std::string, std::vector<listener_info_t>>::iterator it, dispatch_params_t params, bool direct)
{
    dispatch_data_t* data = 0;
    for (auto handler : it->second) {
        uv_async_t* async;
        // NOTE:
        // happens only if its a sq listener
        // and its called from cpp side
        if (!params.array && handler.blob) {
            // trigger callback to create sq function parameter (array)
            Sqrat::Array *array = new Sqrat::Array(((Sqrat::Function*)handler.blob)->GetVM());
            params.arproc(array);
            params.array = array;
        }

        data = new dispatch_data_t { handler, params.event, params.array };

        if (!direct) {
            async = new uv_async_t;
            uv_async_init(uv_default_loop(), async, _callback);
            async->data = (void*)data;
            uv_async_send(async);
        } else {
            void *par = data->info.responder(data->event, data->array);
            data->info.callback(par, data->info.blob);
        }
    }

    if (data) {
        if (!direct) {
            // NOTE(zaklaus): Destroy the event data once we're done with the calls.
            uv_async_t* async = new uv_async_t;
            uv_async_init(uv_default_loop(), async, _cleanup_event);
            async->data = (void *)new dispatch_cleanup_stack_t{ params.event, params.array };
            uv_async_send(async);
        } else {
            delete data;
        }
    }
}

void librg::events::trigger(std::string name, dispatch_params_t params, bool direct)
{
    auto it = _events.find(name);
    if (it != _events.end()) {
        _trigger(it, params, direct);
    }
}

void librg::events::trigger(events_it eventId, dispatch_params_t params, bool direct)
{
    if (eventId != _events.end()) {
        _trigger(eventId, params, direct);
    }
}
