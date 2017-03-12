#include <librg/events.h>

using namespace librg::events;

size_t librg::events::add(std::string name, callback_generic callback, callback_response responder, void *blob)
{
    listener_info_t info { callback, responder, blob };

    if (__events.find(name) != __events.end()) {
        __events[name].push_back(info);
    } else {
        std::vector<listener_info_t> newlist = { info };
        __events.insert(std::make_pair(name, newlist));
    }

    return __events[name].size() - 1;
}
