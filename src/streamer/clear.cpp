#include <librg/streamer.h>

void librg::streamer::clear()
{
    _root.entities.clear();
    _root.trees.clear();
}

void librg::streamer::clear(aabb_t bounds)
{
    clear();
    _root.boundary = bounds;
}
