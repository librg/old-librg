#include "test.hpp"
#include <librg/streamer.h>
#include <librg/utils/aabb.h>
#include <vectorial/vectorial.h>

void streamer_test()
{
    TEST("streamer.h");
    {
        librg::entities_initialize();
        librg::streamer_initialize(1000, 1000);

        auto entity = librg::entities->create();
        entity.assign<librg::streamable_t>(vectorial::vec3f(1000));
        entity.assign<librg::transform_t>();

        IT("should be able to return queue") {

            auto queue = librg::streamer::query(entity);

            EXPECT(queue.size() == 0);
        }

        IT("should be able to return exactly 1 entity") {

            auto friendly = librg::entities->create();
            friendly.assign<librg::streamable_t>(vectorial::vec3f(1000));
            auto ft = librg::transform_t();
            ft.position = vectorial::vec3f(30,20,10);
            friendly.assign<librg::transform_t>(ft);

            librg::streamer::insert(friendly);
            librg::streamer::insert(entity);

            auto queue = librg::streamer::query(entity);

            EXPECT(queue.size() == 1);
        }

        librg::streamer::clear();

        IT("should be able to return exactly 666 entities") {
            for (int i = 0; i < 666; i++) {
                auto enemy = librg::entities->create();
                enemy.assign<librg::streamable_t>(vectorial::vec3f(300));
                auto ft = librg::transform_t();
                ft.position = vectorial::vec3f(i,20,10);
                enemy.assign<librg::transform_t>(ft);

                librg::streamer::insert(enemy);
            }

            auto queue = librg::streamer::query(entity);

            EXPECT(queue.size() == 666);
        }

        librg::streamer_terminate();
        librg::entities_terminate();
    }
}
