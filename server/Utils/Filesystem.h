#ifndef __util_filesystem
#define __util_filesystem

#include <uv.h>
#include <string>

namespace FS
{
    struct fs_result_t {
        int handle;
        uint64_t length;
        uint64_t fplength;
        char* content;
        char* filepath;
        void (*callback)(fs_result_t* result);
    };

    typedef void (*fs_callback)(fs_result_t* result);
    typedef fs_result_t result_t;

    void onRead(uv_fs_t *req);
    bool Read(std::string fileName, fs_callback callback);
}

#endif //__util_filesystem
