// Basic framework test suite.

#ifndef librg_test
#define librg_test

#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <string>

/**
 * Glorious testing suite
 * (ported from sq)
 */
static int __passed = 0;
static int __total  = 0;

using vald_t = std::function<void(bool)>;
using cscb_t = std::function<void(vald_t)>;
using case_t = std::function<void(std::string, cscb_t)>;
using desc_t = std::function<void(case_t)>;

static inline void describe(std::string ent, desc_t descinner) {
    printf("\n  Testing %s:\n", ent.c_str());

    descinner([ent](std::string condition, cscb_t callback) {
        try {
            callback([ent, condition](bool result) {
                if (result) {
                    printf("    \x1B[32m[✓]\x1B[0m %s %s - passed\n", ent.c_str(), condition.c_str()); __passed++;
                }
                else {
                    printf("    \x1B[31m[✗]\x1B[0m %s %s - failed\n", ent.c_str(), condition.c_str());
                }

                __total++;
            });

        }
        catch (std::exception) {
            printf("  \x1B[31m[✗]\x1B[0m %s %s - failed (exception)\n", ent.c_str(), condition.c_str()); __total++;
        }
    });
}

static inline void motd()
{
    puts("Starting librg unit testing...");
}

static inline int results()
{
    printf("\nTotal passed %d/%d, total failed %d.\n", __passed, __total, __total - __passed);
    return __total - __passed;
}

#endif // librg_test
