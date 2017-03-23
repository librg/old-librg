#include <librg/streamer.h>

bool _set_visible_for(std::vector<Entity> &entities, Entity entity, bool state)
{
    auto &b = entities;
    auto query = std::find(b.begin(), b.end(), entity);
    if (query == b.end()) {
        if (state) {
            b.push_back(entity);
            return true;
        } else {
            return false;
        }
    } else {
        if (!state) {
            b.erase(query);
            return true;
        } else {
            return false;
        }
    }
}

bool librg::streamer::set_visible(Entity entity, bool state)
{
    return _set_visible_for(_root.blacklistedEntities, entity, state);
}

bool librg::streamer::set_visible_for(Entity entity, Entity target, bool state)
{
    auto streamable = target.component<streamable_t>();
    if (!streamable) return false;

    auto &ignoredEntities = streamable->ignoredEntities;
    return _set_visible_for(ignoredEntities, entity, state);
}
