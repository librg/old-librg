#include "../test.hpp"
#include <librg/utils/aabb.h>
#include <vectorial/vectorial.h>

void aabb_test() {
    TEST("utils::aabb.h");
    {
        using namespace vectorial;
        using namespace librg;

        auto pinside    = vec3f(2, 2, 2);
        auto poutside   = vec3f(10, 2, 2);

        IT("should be able to create itself") {
            auto sample = aabb_t(vec3f(5, 5, 5));

            EXPECT((sample.halfdim.x() == 5));
        }

        IT("should be able to check if 2d point is inside") {
            EXPECT(aabb_t(vec3f(5, 5, 5)).contains_2d(pinside));
        }

        IT("should be able to check if 2d point is outside") {
            EXPECT(!aabb_t(vec3f(5, 5, 5)).contains_2d(poutside));
        }

        IT("should be able to check if 3d point is inside") {
            EXPECT(aabb_t(vec3f(5, 5, 5)).contains_3d(pinside));
        }

        IT("should be able to check if 3d point is outside") {
            EXPECT(!aabb_t(vec3f(5, 5, 5)).contains_3d(poutside));
        }
    }
}
