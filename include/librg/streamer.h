#ifndef streamer_h
#define streamer_h

#include <librg/entities.h>
#include <vectorial/vectorial.h>
#include <librg/utils/aabb.h>
#include <librg/components/streamable.h>

namespace librg
{
    void streamer_initialize(aabb_t bounds);
    static inline void streamer_terminate() {};

    namespace streamer
    {
        constexpr int MAX_NODES = 4;
        using namespace vectorial;

        struct qtree_t {
            qtree_t() {}
            qtree_t(aabb_t boundary) : boundary(boundary) {}

            void subdivide();
            void create_child(aabb_t boundary);
            bool insert(entityx::Entity entity);
            void query(std::vector<entityx::Entity> &visible, aabb_t range, entityx::ComponentHandle<streamable_t> streamable);

            aabb_t boundary;
            std::vector<entityx::Entity> entities;
            std::vector<entityx::Entity> blacklistedEntities;
            std::vector<qtree_t> trees;
        };

        extern qtree_t _root;

        /**
         * Public API method for inserting an entity to the quad tree.
         * @param entity An entity to insert.
         */
        bool insert(entityx::Entity entity);

        /**
         * Public API method for cleaning up the quad-tree.
         */
        void clear();

        /**
         * Public API method for cleaning up the quad-tree and
         * setting up a new boundary.
         * @param bounds A tree world boundary.
         */
        void clear(aabb_t bounds);

        /**
         * Public API method for querying a list of entities that should be
         * streamed.
         * @param entity An entity to be queried against.
         */
        std::vector<entityx::Entity> query(entityx::Entity entity);
    }
}

#endif // streamer_h
