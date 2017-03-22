#ifndef streamer_h
#define streamer_h

#include <librg/entities.h>
#include <vectorial/vectorial.h>

namespace librg
{
    void streamer_initialize();
    static inline void streamer_terminate() {};

    namespace streamer
    {
        constexpr int MAX_NODES = 4;
        constexpr float MAX_TREE_SIZE = 32*1024;
        using namespace vectorial;

        struct aabb_t {
            aabb_t() : halfdim(0) {}
            aabb_t(float halfdim) : halfdim(halfdim) {}
            aabb_t(vec3f center, float halfdim)
                : center(center), halfdim(halfdim) {}

            bool contains(vec3f point)
            {
                return(center.x() - halfdim <= point.x()
                    && center.x() + halfdim >= point.x()
                    && center.y() - halfdim <= point.y()
                    && center.y() + halfdim >= point.y());
            }

            float halfdim;
            vec3f center;
        };

        struct qtree_t {
            qtree_t() : boundary(MAX_TREE_SIZE) {}
            qtree_t(aabb_t boundary) : boundary(boundary) {}

            void subdivide();
            void create_child(aabb_t boundary);
            bool insert(entityx::Entity entity);

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
        void clean();

        /**
         * Public API method for querying a list of entities that should be
         * streamed.
         * @param entity An entity to be queried against.
         */
        auto query(entityx::Entity entity);


    }
}

#endif // streamer_h
