#include "test.hpp"
#include <librg/streamer.h>
#include <librg/utils/aabb.h>
#include <vectorial/vectorial.h>

void streamer_test()
{
    TEST("streamer.h");
    {
        librg::streamer_initialize(librg::aabb_t(vectorial::vec3f(1000,1000,1000)));

        auto entity = librg::entities->create();

        IT("should be able to return queue") {

            auto queue = librg::streamer::query(entity);

            EXPECT(queue.size() == 0);
        }

        librg::streamer_terminate();
    }
}
