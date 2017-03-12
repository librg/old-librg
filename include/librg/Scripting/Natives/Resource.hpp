#ifndef __scripting_resource
#define __scripting_resource

#include <librg/resources.h>

namespace librg
{
    namespace scripting
    {
        /**
         * Public api
         * check wether or not particular resource has been loaded
         * @param  resourceName
         * @return
         */
        inline static bool resource_loaded(const char *resourceName)
        {
            return librg::resources::exists(resourceName);
        }

        /**
         * Registry method
         * @param native
         */
        inline static void resource_install(Sqrat::Table& native)
        {
            native.Func("resourceLoaded", &resource_loaded);
        }
    }
}

#endif // __scripting_resource
