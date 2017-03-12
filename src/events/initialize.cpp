#include <librg/events.h>

using namespace librg;

std::unordered_map<std::string, std::vector<events::listener_info_t>> events::__events;

void librg::events_initialize()
{
    // hey
}
