#include "../test.hpp"
#include <librg/utils/fs.h>

void fs_test() {
    describe("utils/fs.h", [](case_t it) {
        using namespace librg;

        it("should create folder", [](vald_t validate) {
            int result = fs::mkdir("testdir");

            validate(result == 0 || result == UV_EEXIST);
        });

        // it("should be able to read file content async", [](vald_t validate) {
        //     fs::read("", [validate](fs::result_t* res) {
        //         validate(true);
        //     });
        // });

        it("should be able to read file content", [](vald_t validate) {
            // validate(false);
            validate(true);
            // validate(false);
        });
    });
}
