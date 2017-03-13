#include <librg/events.h>

using namespace librg::events;

size_t librg::events::add(std::string name, callback_generic callback, callback_proxy proxy, void *blob)
{
    listener_info_t info { callback, proxy, blob };

    if (_events.find(name) != _events.end()) {
        _events[name].push_back(info);
    } else {
        std::vector<listener_info_t> newlist = { info };
        _events.insert(std::make_pair(name, newlist));
    }

    return _events[name].size() - 1;
}
