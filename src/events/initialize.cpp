#include <librg/events.h>

using namespace librg;

std::unordered_map<std::string, std::vector<events::listener_info_t>> events::_events;

void librg::events_initialize()
{
    // hey
}
