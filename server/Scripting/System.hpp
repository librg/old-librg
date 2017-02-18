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

    inline static void test2(const char* message, int number, float otherNumber)
    {
        Core::Log("its a test message 2 with: %s, %d, %f", message, number, otherNumber);
    }

    inline static void Install(HSQUIRRELVM vm)
    {
        RootTable(vm).Func("test", &test);
        RootTable(vm).Func("test2", &test2);
    }
}



}
}

#endif // __scripting_system
