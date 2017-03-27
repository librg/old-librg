#ifndef _unit_tests
#define _unit_tests

#include "utils/fs.hpp"
#include "utils/aabb.hpp"
#include "streamer.hpp"
#include "events.hpp"

void run_unit_tests()
{
    // utils
    fs_test();
    aabb_test();

    // main
    streamer_test();
    events_test();
}

#endif // _unit_tests
