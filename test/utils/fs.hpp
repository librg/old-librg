#include "../test.hpp"
#include <librg/utils/fs.h>

void fs_test() {
    TEST("utils::fs");
    {
        IT("should create folder") {
            int result = librg::fs::mkdir("testdir");

            EXPECT(result == 0 || result == UV_EEXIST);
        }
    }
}
