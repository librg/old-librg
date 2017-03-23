#ifndef streamable_h
#define streamable_h

#include <librg/entities.h>
#include <librg/components/transform.h>

namespace librg
{
    struct streamable_t {
        vec3f queryRange;
        std::vector<Entity> ignoredEntities;
    };
}

#endif // streamable_h
