// Copyright ReGuider Team, 2016-2017
//
#include <librg/streamer.h>

using namespace librg;

bool _set_visible_for(std::vector<entity_t> &entities, entity_t entity, bool state)
{
    auto &b = entities;
    auto query = std::find(b.begin(), b.end(), entity);
    if (query == b.end()) {
        if (!state) {
            b.push_back(entity);
            return true;
        } else {
            return false;
        }
    } else {
        if (state) {
            b.erase(query);
            return true;
        } else {
            return false;
        }
    }
}

bool librg::streamer::set_visible(entity_t entity, bool state)
{
    return _set_visible_for(_root.blacklistedEntities, entity, state);
}

bool librg::streamer::set_visible_for(entity_t target, entity_t entity, bool state)
{
    auto streamable = target.component<streamable_t>();
    if (!streamable) return false;

    auto &ignoredEntities = streamable->ignored;
    return _set_visible_for(ignoredEntities, entity, state);
}
