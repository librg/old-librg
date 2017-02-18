#ifndef __scripting_system
#define __scripting_system

using namespace Sqrat;

namespace Server    {
namespace Scripting {


namespace System
{
    inline static void test(const char* message)
    {
        Core::Log("its a test message: %s", message);
    }

    inline static void Install(HSQUIRRELVM vm)
    {
        RootTable(vm).Func("test", &test);
    }
}



}
}

#endif // __scripting_system
