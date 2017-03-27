#include <librg/events.h>

using namespace librg;

void librg::events_terminate()
{
    events::_events.clear();
}
