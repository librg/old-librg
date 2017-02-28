#ifndef __scripting_system
#define __scripting_system

namespace Server    {
namespace Scripting {


namespace System
{
    /**
     * TODO: remove
     * @param message [description]
     */
    inline static void test(const char* message)
    {
        Core::Log("its a test message: %s", message);
    }

    /**
     * TODO: remove
     * @param message     [description]
     * @param number      [description]
     * @param otherNumber [description]
     */
    inline static void test2(const char* message, int number, float otherNumber)
    {
        Core::Log("its a test message 2 with: %s, %d, %f", message, number, otherNumber);
    }

    /**
     * Registry method
     * @param native
     */
    inline static void Install(Sqrat::Table& native)
    {
        native.Func("test",  &test);
        native.Func("test2", &test2);
    }
}


} // Scripting
} // Server


#endif // __scripting_system
