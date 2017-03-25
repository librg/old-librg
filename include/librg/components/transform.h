#ifndef librg_components_transform_h
#define librg_components_transform_h

#include <vectorial/vectorial.h>

namespace librg
{
    using namespace vectorial;

    struct transform_t {
        transform_t() = default;
        transform_t(vec3f position, vec3f rotation, vec3f scale)
        : position(position), rotation(rotation), scale(scale) {}

        vec3f position;
        vec3f rotation;
        vec3f scale;
    };
}

#endif // librg_components_transform_h
