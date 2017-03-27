#include "../test.hpp"
#include <librg/utils/aabb.h>
#include <vectorial/vectorial.h>

void aabb_test() {
    describe("utils/aabb.h", [](case_t it) {
        using namespace vectorial;
        using namespace librg;

        auto pinside    = vec3f(2, 2, 2);
        auto poutside   = vec3f(10, 2, 2);

        it("should be able to create itself", [](vald_t validate) {
            auto sample = aabb_t(vec3f(5, 5, 5));
            validate((sample.halfdim.x() == 5));
        });

        it("should be able to check if 2d point is inside", [pinside](vald_t validate) {
            validate(aabb_t(vec3f(5, 5, 5)).contains_2d(pinside));
        });

        it("should be able to check if 2d point is outside", [poutside](vald_t validate) {
            validate(!aabb_t(vec3f(5, 5, 5)).contains_2d(poutside));
        });

        it("should be able to check if 3d point is inside", [pinside](vald_t validate) {
            validate(aabb_t(vec3f(5, 5, 5)).contains_3d(pinside));
        });

        it("should be able to check if 3d point is outside", [poutside](vald_t validate) {
            validate(!aabb_t(vec3f(5, 5, 5)).contains_3d(poutside));
        });
    });
}
