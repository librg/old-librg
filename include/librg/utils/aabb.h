#ifndef librg_utils_aabb_h
#define librg_utils_aabb_h

// TODO(zaklaus): Probably move to a better place!

#include <vectorial/vectorial.h>
#include <complex> // std::abs

namespace librg
{
    using namespace vectorial;

    struct aabb_t {
        aabb_t() {}
        aabb_t(vec3f halfdim) : halfdim(halfdim) {}
        aabb_t(vec3f center, vec3f halfdim)
            : center(center), halfdim(halfdim) {}

        bool contains_2d(vec3f point)
        {
            return(center.x() - halfdim.x() <= point.x()
                && center.x() + halfdim.x() >= point.x()
                && center.y() - halfdim.y() <= point.y()
                && center.y() + halfdim.y() >= point.y());
        }

        bool contains_3d(vec3f point)
        {
            return(center.x() - halfdim.x() <= point.x()
                && center.x() + halfdim.x() >= point.x()
                && center.y() - halfdim.y() <= point.y()
                && center.y() + halfdim.y() >= point.y()
                && center.z() - halfdim.z() <= point.z()
                && center.z() + halfdim.z() >= point.z());
        }

        bool intersects_2d(aabb_t rhs)
        {
            if (std::abs(center.x() - rhs.center.x()) > (halfdim.x() + rhs.halfdim.x())) return false;
            if (std::abs(center.y() - rhs.center.y()) > (halfdim.y() + rhs.halfdim.y())) return false;

            return true;
        }

        bool intersects_3d(aabb_t rhs)
        {
            if (std::abs(center.x() - rhs.center.x()) > (halfdim.x() + rhs.halfdim.x())) return false;
            if (std::abs(center.y() - rhs.center.y()) > (halfdim.y() + rhs.halfdim.y())) return false;
            if (std::abs(center.z() - rhs.center.z()) > (halfdim.z() + rhs.halfdim.z())) return false;

            return true;
        }

        vec3f halfdim;
        vec3f center;
    };
}

#endif // librg_utils_aabb_h
