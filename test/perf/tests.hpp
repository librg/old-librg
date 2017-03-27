#ifndef _perf_tests
#define _perf_tests

#include "events.hpp"

namespace performance
{
    void run_tests()
    {
        printf("%s\n", "\nRunning performance tests.");
        events_test();
    }
}
#endif // _perf_tests
