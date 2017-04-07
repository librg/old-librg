// Copyright ReGuider Team, 2016-2017
//
#include <librg/streamer.h>
#include <librg/entities.h>
#include <librg/components/streamable.h>

librg::streamer::qtree_t librg::streamer::_root;

/**
 * Storage for client cache
 * TODO(inlife): rethink and refactor
 */
std::unordered_map<uint64_t, librg::entity_t> librg::streamer::client_cache;

/**
 * Storage for queue of entities marked
 * for deletion in the next update
 */
std::vector<librg::entity_t> librg::streamer::remove_queue;


void librg::streamer_initialize()
{
    streamer::_root.boundary = aabb_t(vectorial::vec3f(5000, 5000, 0.f)); // TODO(inlife); move to set_size method

    librg::_systems->add<entityx::deps::Dependency<streamable_t, transform_t>>();
}
