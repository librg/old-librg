#ifndef streamable_h
#define streamable_h

#include <librg/entities.h>
#include <librg/components/transform.h>

namespace librg
{
    struct streamable_t {
        float queryRange;

        // TODO(zaklaus): Add blacklist vector for filtering out unwanted entities.
    };
}

#endif // streamable_h
