#include <librg/events.h>

bool librg::events::remove(std::string name, size_t handler)
{
    if (__events.find(name) == __events.end()) return false;

    try {
        __events[name].erase(__events[name].begin()+handler);
    }
    catch(std::exception ex) {
        // TODO(zaklaus): Print error message here! YES!
    }

    return true;
}
