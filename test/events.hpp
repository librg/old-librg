#include "test.hpp"
#include <librg/events.h>

#include <string>

int number = 5;

// event data format
struct test_event_t {
    int num;
    int add;
};

void* test_event_proxy(const void *data, Sqrat::Array *array)
{
    if (array) {
        auto num = array->Pop().Cast<int>();
        auto add = array->Pop().Cast<int>();
        auto testData = new test_event_t { num, add };
        return (void *)testData;
    }
    return (void *)data;
}

void test_event_cb(const void* data, void* /* blob */)
{
    auto testData = (test_event_t *)data;
    number += testData->add * testData->num;
}

void events_test()
{
    describe("events.h", [](case_t it) {

        librg::events_initialize();

        it("should be able to register an event", [](vald_t validate) {
            auto done = librg::events::add("testEvent", test_event_cb, test_event_proxy);

            validate(done != -1);
        });

        it("should be able to trigger an event", [](vald_t validate) {
            int adder = 10;
            int mult  = 2;
            auto testData = new test_event_t { adder, mult };

            librg::events::trigger("testEvent", EVENT_PARAM(testData, [=](Sqrat::Array *array) {
                array->Append(adder);
                array->Append(mult);
            }), true);

            validate(number == 25);
        });

        librg::events_terminate();
    });
}
