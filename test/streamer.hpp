#include "test.hpp"
#include <librg/streamer.h>
#include <librg/utils/aabb.h>
#include <vectorial/vectorial.h>
#include <chrono>

void streamer_test()
{
    using namespace std::chrono;

    describe("streamer.h", [](case_t it) {

        librg::entities_initialize();
        librg::streamer_initialize(4000, 4000);

        auto entity = librg::entities->create();
        entity.assign<librg::streamable_t>(vectorial::vec3f(1000));
        entity.assign<librg::transform_t>();

        it("should be able to return queue", [entity](vald_t validate) {

            auto queue = librg::streamer::query(entity);

            validate(queue.size() == 0);
        });

        it("should be able to return exactly 1 entity", [entity](vald_t validate) {

            auto friendly = librg::entities->create();
            friendly.assign<librg::streamable_t>(vectorial::vec3f(1000));
            auto ft = librg::transform_t();
            ft.position = vectorial::vec3f(30,20,10);
            friendly.assign<librg::transform_t>(ft);

            librg::streamer::insert(friendly);
            librg::streamer::insert(entity);

            auto queue = librg::streamer::query(entity);

            validate(queue.size() == 1);
        });

        librg::streamer::clear();

        it("should be able to return exactly 666 entities", [entity](vald_t validate) {
            for (int i = 0; i < 666; i++) {
                auto enemy = librg::entities->create();
                enemy.assign<librg::streamable_t>(vectorial::vec3f(300));
                auto ft = librg::transform_t();
                ft.position = vectorial::vec3f((float)i,20,10);
                enemy.assign<librg::transform_t>(ft);

                librg::streamer::insert(enemy);
            }

            auto queue = librg::streamer::query(entity);

            validate(queue.size() == 666);
        });

        librg::streamer::clear();

        it("should be able to return less than 32k entities", [entity](vald_t validate) {
            auto newEntity = librg::entities->create();
            newEntity.assign<librg::streamable_t>(vectorial::vec3f(30000));
            newEntity.assign<librg::transform_t>();
            for (int i = 0; i < 48000; i++) {
                srand(i);
                auto enemy = librg::entities->create();
                enemy.assign<librg::streamable_t>(vectorial::vec3f(300));
                auto ft = librg::transform_t();
                ft.position = vectorial::vec3f((float)i,30.f,10);
                enemy.assign<librg::transform_t>(ft);

                librg::streamer::insert(enemy);
            }
            auto queue = librg::streamer::query(newEntity);
            validate(queue.size() <= 32000);
        });

        librg::streamer::clear();

        it("should be able to blacklist 1 entity globally", [entity](vald_t validate) {
            auto badEntity = librg::entities->create();
            badEntity.assign<librg::streamable_t>(vectorial::vec3f(100));
            badEntity.assign<librg::transform_t>();
            librg::streamer::set_visible(badEntity, false);

            auto goodEntity = librg::entities->create();
            goodEntity.assign<librg::streamable_t>(vectorial::vec3f(100));
            goodEntity.assign<librg::transform_t>();

            librg::streamer::insert(badEntity);
            librg::streamer::insert(goodEntity);

            auto queue = librg::streamer::query(entity);
            validate(queue.size() == 1);
        });

        librg::streamer::clear();

        it("should be able to ignore 1 entity for target entity", [entity](vald_t validate) {
            auto badEntity = librg::entities->create();
            badEntity.assign<librg::streamable_t>(vectorial::vec3f(100));
            badEntity.assign<librg::transform_t>();
            librg::streamer::set_visible(badEntity, false);

            auto goodEntity = librg::entities->create();
            goodEntity.assign<librg::streamable_t>(vectorial::vec3f(100));
            goodEntity.assign<librg::transform_t>();

            auto targetEntity = librg::entities->create();
            targetEntity.assign<librg::streamable_t>(vectorial::vec3f(100));
            targetEntity.assign<librg::transform_t>();

            librg::streamer::insert(badEntity);
            librg::streamer::insert(goodEntity);

            librg::streamer::set_visible_for(targetEntity, badEntity, false);

            auto queue = librg::streamer::query(targetEntity);
            validate(queue.size() == 1);
        });
    });
}
