#include <librg/streamer.h>
#include <librg/components/transform.h>

bool librg::streamer::qtree_t::insert(entityx::Entity entity)
{
    entityx::ComponentHandle<transform_t> transform = entity.component<transform_t>();
    if (!transform) return false;

    vectorial::vec3f point = transform->position;

    if (!boundary.contains_2d(point)) {
        return false;
    }

    if (entities.size() < MAX_NODES) {
        entities.push_back(entity);
        return true;
    }

    if (trees.size() == 0) {
        subdivide();
    }

    for (auto &tree : trees) {
        if (tree.insert(entity)) return true;
    }

    return false;
}

bool librg::streamer::insert(entityx::Entity entity)
{
    return _root.insert(entity);
}
