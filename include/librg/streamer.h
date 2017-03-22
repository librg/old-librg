#ifndef streamer_h
#define streamer_h

#include <entityx/entityx.h>

namespace librg
{
    void streamer_initialize();
    static inline void streamer_terminate() {};

    namespace streamer
    {
        /**
         * Public API method for building our world representation.
         * @param entities An array of entities.
         */
        void build(std::vector<entityx::Entity> entities);

        /**
         * Public API method for querying a list of entities that should be
         * streamed.
         * @param entity An entity to be queried against.
         */
        auto query(entityx::Entity entity);


    }
}

#endif // streamer_h
