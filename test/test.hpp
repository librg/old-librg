// Basic framework test suite.

#include <stdio.h>
#include <stdlib.h>

static int gTotal  = 0;
static int gPassed = 0;

#define TEST_STRINGIFY(name) #name
#define TEST(name) printf("Category: %s\n", name);
#define IT(req) printf("- It %s\t", req); ++gTotal;
#define EXPECT(cond) if(cond) { printf("%s\n", "[PASS]"); ++gPassed; } else { printf("%s\n", "[FAIL]"); } puts(" ");

static inline void motd()
{
    puts("ReGuider Unit Testing utility.\n");
}

static inline int results()
{
    printf("Tests passed:\t%d\n", gPassed);
    printf("Tests failed:\t%d\n", gTotal-gPassed);
    printf("Total tests:\t%d\n",  gTotal);

    return gTotal - gPassed;
}
