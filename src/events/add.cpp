#include <librg/events.h>

using namespace librg::events;

events_it librg::events::add(std::string name, callback_generic callback, callback_proxy proxy, void *blob)
{
    listener_info_t info { callback, proxy, blob };

    auto it = _events.find(name);

    if (it != _events.end()) {
        _events[name].push_back(info);
    } else {
        std::vector<listener_info_t> newlist = { info };
        _events.insert(std::make_pair(name, newlist));

        // TODO(zaklaus): Figure this one out later.
        return _events.find(name);
    }

    return it;
}
