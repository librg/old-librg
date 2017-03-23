#ifndef streamable_h
#define streamable_h

#include <librg/entities.h>
#include <librg/components/transform.h>

namespace librg
{
    struct streamable_t {
        float queryRange;
        std::vector<entityx::Entity> ignoredEntities;
    };
}

#endif // streamable_h
