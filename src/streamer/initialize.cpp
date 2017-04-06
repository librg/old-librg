// Copyright ReGuider Team, 2016-2017
//
#include <librg/streamer.h>
#include <librg/components/streamable.h>

librg::streamer::qtree_t librg::streamer::_root;

void librg::streamer_initialize()
{
    streamer::_root.boundary = aabb_t(vectorial::vec3f(5000, 5000, 0.f)); // TODO(inlife); move to set_size method

    librg::_systems->add<entityx::deps::Dependency<streamable_t, transform_t>>();
}
