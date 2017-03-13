#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4312)
#pragma warning(disable:4577)
// #pragma warning(disable:4477)
// #pragma warning(disable:4334)
#endif

#if WIN32
inline void uv_sleep(int milis) {
    Sleep(milis);
}
#else
#include <unistd.h>
inline void uv_sleep(int milis) {
    usleep(milis * 1000);
}
#endif
