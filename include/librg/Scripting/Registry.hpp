#ifndef __scripting_registry
#define __scripting_registry

#include "natives/event.hpp"
#include "natives/entity.hpp"
#include "natives/system.hpp"
#include "natives/timer.hpp"
#include "natives/resource.hpp"

namespace librg
{
    namespace scripting
    {
        /**
         * All our bingings are going in there
         */
        inline static void registry_install(Sqrat::Table& native)
        {
            event_install(native);
            entity_install(native);
            system_install(native);
            timer_install(native);
            resource_install(native);
        }
    }
}

#endif // __scripting_registry
