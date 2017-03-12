#define RGCLIENT

#include <uv.h>

#include "shared.h"

namespace librg
{
    namespace core
    {
        void client(int argc, char * argv[]);
        void client_tick();
    }
}
