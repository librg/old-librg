// Copyright ReGuider Team, 2016-2017
//
#include <librg/streamer.h>

bool librg::streamer::qtree_t::remove(Entity entity)
{
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);
    } else {
        for (auto &tree : trees) {
            if (tree.remove(entity)) return true;
        }
        return false;
    }
    return true;
}

bool librg::streamer::remove(Entity entity)
{
    return _root.remove(entity);
}
