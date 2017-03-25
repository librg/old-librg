#ifndef librg_components_streamable_h
#define librg_components_streamable_h

#include <librg/entities.h>
#include <librg/components/transform.h>

namespace librg
{
    struct streamable_t {
        streamable_t(): queryRange(250) {}
        streamable_t(vec3f queryRange): queryRange(queryRange), ignoredEntities() {}
        vec3f queryRange;
        std::vector<Entity> ignoredEntities;
    };
}

#endif // librg_components_streamable_h
