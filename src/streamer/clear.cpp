// Copyright ReGuider Team, 2016-2017
//
#include <librg/streamer.h>

void librg::streamer::qtree_t::clear()
{
    entities.clear();
    blacklistedEntities.clear();

    for (auto &tree : trees) {
        tree.clear();
    }

    trees.clear();
}

void librg::streamer::clear()
{
    _root.clear();

    for (auto entity : librg::streamer::remove_queue) {
        entity.destroy();
    }

    librg::streamer::remove_queue.clear();
}

void librg::streamer::clear(aabb_t bounds)
{
    clear();
    _root.boundary = bounds;
}
