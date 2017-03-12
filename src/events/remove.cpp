#include <librg/events.h>

bool librg::events::remove(std::string name, size_t handler)
{
    if (_events.find(name) == _events.end()) return false;

    try {
        _events[name].erase(_events[name].begin()+handler);
    }
    catch(std::exception ex) {
        // TODO(zaklaus): Print error message here! YES!
    }

    return true;
}
