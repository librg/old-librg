// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>

using namespace librg;

/**
 * WARNING: UGLY
 * TODO(inlife): refactor
 */
void core::error(const char* format, ...)
{
    va_list ap;
    char message[1024] = { 0 };
    va_start(ap, format);
    vsprintf(message, format, ap);
    va_end(ap);

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    // TODO(inlife): move to async trigger -> callback
    printf("[SERVER][%s] - %s\n", buf, message);
}

/**
 * WARNING: UGLY
 * TODO(inlife): refactor
 */
void core::log(const char* format, ...)
{
    va_list ap;
    char message[1024] = { 0 };
    va_start(ap, format);
    vsprintf(message, format, ap);
    va_end(ap);

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    // TODO(inlife): move to async trigger -> callback
    printf("[SERVER][%s] - %s\n", buf, message);
}
