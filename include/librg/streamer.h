#ifndef streamer_h
#define streamer_h

#include <librg/entities.h>
#include <vectorial/vectorial.h>
#include <librg/utils/aabb.h>

namespace librg
{
    void streamer_initialize();
    static inline void streamer_terminate() {};

    namespace streamer
    {
        constexpr int MAX_NODES = 4;
        constexpr float MAX_TREE_SIZE = 32*1024;
        using namespace vectorial;

        struct qtree_t {
            qtree_t() : boundary(MAX_TREE_SIZE) {}
            qtree_t(aabb_t boundary) : boundary(boundary) {}

            void subdivide();
            void create_child(aabb_t boundary);
            bool insert(entityx::Entity entity);
            void query(std::vector<entityx::Entity> &visible, aabb_t range);

            aabb_t boundary;
            std::vector<entityx::Entity> entities;
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
         * Public API method for querying a list of entities that should be
         * streamed.
         * @param entity An entity to be queried against.
         */
        auto query(entityx::Entity entity) -> std::vector<entityx::Entity>;


    }
}

#endif // streamer_h
