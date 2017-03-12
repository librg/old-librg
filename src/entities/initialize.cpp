#include <librg/entities.h>

entityx::EventManager*  librg::__events;
entityx::EntityManager* librg::entities;
entityx::SystemManager* librg::__systems;

void librg::entities_initialize()
{
    librg::__events  = new entityx::EventManager();
    librg::entities  = new entityx::EntityManager(*librg::__events);
    librg::__systems = new entityx::SystemManager(*librg::entities, *librg::__events);
}
