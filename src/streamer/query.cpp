#include <librg/streamer.h>

void librg::streamer::qtree_t::query(std::vector<Entity> &visible,
                                    aabb_t range, ComponentHandle<streamable_t> streamable)
{
    if (!boundary.intersects(range)) return;
    std::vector<Entity> ignoredEntities = streamable->ignoredEntities;

    for (auto &entity : entities) {
        auto position = entity.component<transform_t>()->position;
        if (   range.contains(position)
            && std::find(ignoredEntities.begin(),
                         ignoredEntities.end(),
                         entity) == ignoredEntities.end()
            && std::find(blacklistedEntities.begin(),
                         blacklistedEntities.end(),
                         entity) == blacklistedEntities.end()) {
            visible.push_back(entity);
        }
    }

    if (trees.size() == 0) return;

    for (auto &tree : trees) {
        tree.query(visible, range, streamable);
    }
}

std::vector<Entity> librg::streamer::query(Entity entity)
{
    auto visible = std::vector<Entity>();

    auto streamable = entity.component<streamable_t>();
    if (!streamable) return visible;

    auto transform  = entity.component<transform_t>();

    auto qrange   = streamable->queryRange;
    auto position = transform->position;
    auto range    = aabb_t(position, qrange);

    _root.query(visible, range, streamable);

    return visible;
}
