#ifndef _util_fs
#define _util_fs

#include <uv.h>
#include <string>
#include <functional>

namespace librg
{
    namespace fs
    {
        struct fs_result_t {
            int handle;
            uint64_t length;
            uint64_t fplength;
            char* content;
            char* filepath;
            std::function<void(fs_result_t*)> callback;
        };

        void private_onread(uv_fs_t *req);

    #ifdef WIN32
        static char separator = '\\';
    #else
        static char separator = '/';
    #endif

        // define callback and aliases
        typedef std::function<void(fs_result_t*)> callback;
        typedef fs_result_t result_t;

        // async
        bool read(std::string filename, callback callback);

        // sync
        int mkdir(std::string filename);

        // ugly
        using _s = std::string;
        static char _p = separator;
        static inline _s path(_s a1, _s a2) {return a1+_p+a2;}
        static inline _s path(_s a1, _s a2, _s a3) {return a1+_p+a2+_p+a3;}
        static inline _s path(_s a1, _s a2, _s a3, _s a4) {return a1+_p+a2+_p+a3+_p+a4;}
        static inline _s path(_s a1, _s a2, _s a3, _s a4, _s a5) {return a1+_p+a2+_p+a3+_p+a4+_p+a5;}
        static inline _s path(_s a1, _s a2, _s a3, _s a4, _s a5, _s a6) {return a1+_p+a2+_p+a3+_p+a4+_p+a5+_p+a6;}
        static inline _s path(_s a1, _s a2, _s a3, _s a4, _s a5, _s a6, _s a7) {return a1+_p+a2+_p+a3+_p+a4+_p+a5+_p+a6+_p+a7;}
        static inline _s path(_s a1, _s a2, _s a3, _s a4, _s a5, _s a6, _s a7, _s a8) {return a1+_p+a2+_p+a3+_p+a4+_p+a5+_p+a6+_p+a7+_p+a8;}
    }
}

#endif //_util_fs
