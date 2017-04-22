// Copyright ReGuider Team, 2016-2017
//
#include <librg/events.h>

using namespace librg;

void events::trigger(uint16_t id, events::event_t* event)
{
    auto size = events::event_handlers[id].size();

    switch (size) {
        case 1:
            events::event_handlers[id][0](event);
        break;
        case 0: return; break;
        default:
            for (auto event_handler : events::event_handlers[id]) {
                event_handler(event);
            }
        break;
    }
}
