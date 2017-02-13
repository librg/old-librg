#ifndef __resource_resource
#define __resource_resource

#include <squirrel.h>

namespace Server    {
namespace Resource  {

class Resource {
public:
    Resource();
    ~Resource();

private:
    HSQUIRRELVM mVM;
};

}
}

#endif //__resource_resource
