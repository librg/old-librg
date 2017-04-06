#include <librg/streamer.h>

namespace performance
{
    void streamer_test()
    {
        benchmark("streamer.h", [](perc_t test) {

            librg::entities_initialize();
            librg::streamer_initialize();
            librg::streamer::clear();

            auto entity = librg::entities->create();
            entity.assign<librg::streamable_t>(vectorial::vec3f(250));
            entity.assign<librg::transform_t>();

            test("insertion and deletion of 48k entities", [entity]() {
                srand(0xDEADBEEF);
                for (int i = 0; i < 48000; i++) {
                    auto enemy = librg::entities->create();
                    enemy.assign<librg::streamable_t>(vectorial::vec3f(300));
                    auto ft = librg::transform_t();
                    ft.position = vectorial::vec3f((float)(2000 - rand() % 4000),(float)(2000 - rand() % 4000),10);
                    enemy.assign<librg::transform_t>(ft);

                    librg::streamer::insert(enemy);
                    librg::streamer::clear();
                }
            });

            for (int i = 0; i < 48000; i++) {
                auto enemy = librg::entities->create();
                enemy.assign<librg::streamable_t>(vectorial::vec3f(300));
                auto ft = librg::transform_t();
                ft.position = vectorial::vec3f(i,i,10);
                enemy.assign<librg::transform_t>(ft);

                librg::streamer::insert(enemy);
            }

            test("query of 48k entities with 250 units query range", [entity]() {
                auto queue = librg::streamer::query(entity);
            });

            librg::streamer_terminate();
            librg::entities_terminate();
        });
    }
}
