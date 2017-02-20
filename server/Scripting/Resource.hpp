#ifndef __scripting_resource
#define __scripting_resource

#include <Resource/Manager.h>

using namespace Sqrat;

namespace Server    {
namespace Scripting {


namespace Resource
{
    inline static bool resourceLoaded(const char* resourceName)
    {
        return Server::Resource::Manager::Instance()->Exist(resourceName);
    }

    inline static void Install(Table& table)
    {
        table.Func("resourceLoaded", &resourceLoaded);
    }
}



}
}

#endif // __scripting_resource
