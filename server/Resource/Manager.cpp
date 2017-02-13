#include <Core.h>
#include "Manager.h"

#include <Utils/Filesystem.h>

using namespace Server;

const char* FILE_STRUCTURE[] = {
    "resources",
    "meta.xml",
};

// TODO(inlife): move to config.xml?
std::vector<std::string> resources = {
    "default2",
    "default",
};

Resource::Manager::Manager()
{
    uv_fs_mkdir(uv_default_loop(), new uv_fs_t, FILE_STRUCTURE[0], 0755, [] (uv_fs_t* req) -> void {
        if (req->result && req->result != UV_EEXIST) {
            Core::Error(uv_strerror((int)req->result));
            delete req;
            return;
        }

        for (auto resource : resources) {
            FS::Read(std::string(FILE_STRUCTURE[0]) + DS + resource + DS + FILE_STRUCTURE[1], [] (FS::result_t* result) -> void {
                printf("%.*s\n", (int)result->length, result->content);
            });
        }

        Resource::Manager::Instance()->Init();
        delete req;
    });
}

Resource::Manager::~Manager()
{

}

void Resource::Manager::Init()
{
}
