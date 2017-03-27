#include <librg/entities.h>

void librg::entities_terminate()
{
    delete librg::_systems;
    delete librg::entities;
    delete librg::_events;
}
