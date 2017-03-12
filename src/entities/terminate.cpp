#include <librg/entities.h>

void librg::entities_terminate()
{
    delete librg::_events;
    delete librg::entities;
    delete librg::_systems;
}
