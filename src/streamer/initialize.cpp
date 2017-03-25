#include <librg/streamer.h>
#include <librg/components/streamable.h>

librg::streamer::qtree_t librg::streamer::_root;

void librg::streamer_initialize(float width, float height)
{
    streamer::_root.boundary = aabb_t(vectorial::vec3f(width, height, 0.f));

    librg::_systems->add<entityx::deps::Dependency<streamable_t, transform_t>>();
}
