#include <librg/entities.h>

void librg::entities_terminate()
{
    delete librg::__events;
    delete librg::entities;
    delete librg::__systems;
}
