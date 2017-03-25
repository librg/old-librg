#include "test.hpp"
#include <librg/events.h>

void events_test()
{
    describe("events.h", [](case_t it) {

        librg::events_initialize();

        it("should be able to waat", [](vald_t validate) {
            validate(true);
        });

        librg::events_terminate();
    });
}
