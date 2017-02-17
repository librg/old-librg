#ifndef __scripting__system
#define __scripting__system

#include <squirrel.h>
#include <sqrat.h>
#include <Core.h>

// // SQInteger mySqFunc(HSQUIRRELVM vm) {
// //     Server::Core::Log("wtf");
// //     return 0;
// // }

// void myPrint(const char* message) {
//     Server::Core::Log(message);
// }

// void BindSquirrel(HSQUIRRELVM vm) {
//     using namespace Sqrat;

//     DefaultVM::Set(vm);
//     // RootTable().SquirrelFunc("print", &mySqFunc);
//     RootTable().Func("print", &myPrint);

//     try {
//         Script script1, script2;

//         script1.CompileString("::print(\"Hello World\");");
//         // script2.CompileFile("/Path/to/Script.nut");

//         script1.Run();
//         // script2.Run();
//     } catch( Exception ) {
//         // Handle exceptions here
//     }

//     // );

//     // RootTable().Bind("MyClass", Class<MyClass>()
//     //     .Func("Foo", &MyClass::Foo)
//     //     .Var("bar", &MyClass::Bar)
//     // );
// }

namespace Server    {
namespace Scripting {


namespace System
{
    inline static void install(HSQUIRRELVM vm)
    {
        RootTable(vm).Func("print", &myPrint);
    }
}



}
}

#endif // __scripting__system
