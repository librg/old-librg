// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_streamer_h
#define librg_streamer_h

#include <vectorial/vectorial.h>

#include <librg/entities.h>
#include <librg/utils/aabb.h>
#include <librg/components/streamable.h>

namespace librg
{
    void streamer_initialize(float width, float height);
    void streamer_terminate();

    namespace streamer
    {
        constexpr int MAX_NODES = 4;
        using namespace vectorial;

        struct qtree_t {
            qtree_t() {}
            qtree_t(aabb_t boundary) : boundary(boundary),
                                       entities(),
                                       blacklistedEntities(),
                                       trees() {}

            void subdivide();
            void create_child(aabb_t boundary);
            bool insert(Entity entity);
            bool remove(Entity entity);
            void clear();
            void query(std::vector<Entity> &visible, aabb_t range, ComponentHandle<streamable_t> streamable, Entity caller);

            aabb_t boundary;
            std::vector<Entity> entities;
            std::vector<Entity> blacklistedEntities;
            std::vector<qtree_t> trees;
        };

        extern qtree_t _root;

        /**
         * Public API method for inserting an entity to the quad tree.
         * @param entity An entity to insert.
         */
        bool insert(Entity entity);

        /**
         * [remove description]
         * @param  entity [description]
         * @return        [description]
         */
        bool remove(Entity entity);

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
        std::vector<Entity> query(Entity entity);

        /**
         * Public API method for setting the global visibility of the entity.
         * @param  entity An entity to deal with.
         * @param  state  A visibility state.
         * @return        Returns zero if no change has happened, one otherwise.
         */
        bool set_visible(Entity entity, bool state);

        /**
         * Public API method for setting visibility of the entity for a specific
         * entity target.
         *
         * Only works if the target entity has a streamable component.
         *
         * @param  target An entity target we relate entity state with.
         * @param  entity An entity we set states for.
         * @param  state  A visibility state.
         * @return        Returns zero if no change has happened, one otherwise.
         */
        bool set_visible_for(Entity target, Entity entity, bool state);
    }

    namespace streamer_callbacks
    {
        using callback_t = std::function<void(uint64_t, uint8_t, Entity, void *)>;

        enum actions {
            create,
            update,
            remove,
            interpolate,
        };

        /**
         * Public Client API method
         * should be used to register handler
         * for entities which were just created and first-time synced
         * from the server (for current stream-zone)
         * @param callback
         */
        void set(actions action, callback_t callback);

        /**
         * Private method
         */
        void trigger(actions action, uint64_t, uint8_t, Entity, void *);

        extern std::unordered_map<uint64_t, Entity> client_cache;
    }
}

#endif // librg_streamer_h
