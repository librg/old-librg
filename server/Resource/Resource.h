#ifndef __resource_resource
#define __resource_resource

#include <vector>
#include <squirrel.h>

namespace Server    {
namespace Resource  {


enum scriptType {
    tServer,
    tClient,
};

struct script_t {
    std::string* filename;
    scriptType type;
};

class Resource {
public:
    Resource(std::string, std::vector<script_t*>);
    ~Resource();

    void Start();
    void Stop();
    void Unload();
    inline bool IsRunning() {
        return false;
    };

private:
    HSQUIRRELVM mVM;
    std::vector<script_t*> mScripts;
    std::string mName;
};


}
}

#endif //__resource_resource
