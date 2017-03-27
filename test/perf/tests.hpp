#ifndef librg_perf_tests
#define librg_perf_tests

#include "events.hpp"

namespace performance
{
    void run_tests()
    {
        printf("%s\n", "\nRunning performance tests.");
        events_test();
    }
}
#endif // librg_perf_tests
