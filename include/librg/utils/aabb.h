#ifndef aabb_h
#define aabb_h

// TODO(zaklaus): Probably move to a better place!

#include <vectorial/vectorial.h>

namespace librg
{
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

        bool intersects(aabb_t rhs)
        {
            // TODO(zaklaus): Implement AABB intersection check.
            return false;
        }

        float halfdim;
        vec3f center;
    };
}

#endif // aabb_h
