#include <librg/streamer.h>

void librg::streamer::qtree_t::clear()
{
    entities.clear();

    for (auto &tree : trees) {
        tree.clear();
    }

    trees.clear();
}

void librg::streamer::clear()
{
    _root.clear();
}

void librg::streamer::clear(aabb_t bounds)
{
    clear();
    _root.boundary = bounds;
}
