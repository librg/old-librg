#ifndef __resource_resource
#define __resource_resource

#include <vector>
#include <squirrel.h>

namespace Server::Resource {
    enum scriptType {
        tServer,
        tClient,
        tShared,
    };

    struct script_t {
        std::string* filename;
        scriptType type;
    };

    class Resource {
    public:
        Resource(std::string, std::vector<script_t*>);
        ~Resource();

        bool Start();
        bool Stop();
        inline bool IsRunning() {
            return mRunning;
        };

    private:
        HSQUIRRELVM mVM;
        std::vector<script_t*> mScripts;
        std::string mName;
        bool mRunning;
    };
}

#endif //__resource_resource
