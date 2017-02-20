#ifndef __scripting_registry
#define __scripting_registry

#include "Natives/Event.hpp"
#include "Natives/System.hpp"
#include "Natives/Timer.hpp"
#include "Natives/Resource.hpp"

namespace Server    {
namespace Scripting {

namespace Registry
{
    /**
     * All our bingings are going in there
     */
    inline static void Install(Sqrat::Table& native)
    {
        Event::Install(native);
        System::Install(native);
        Timer::Install(native);
        Resource::Install(native);
        // System::Install(vm);
        // System::Install(vm);
        // System::Install(vm);
        // System::Install(vm);
        // System::Install(vm);
    }

}



} // Scripting
} // Server

#endif // __scripting_registry
