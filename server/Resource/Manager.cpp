#include <Core.h>
#include "Manager.h"

#include <Utils/Filesystem.h>
#include <tinyxml2.h>

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
    // try to create resources folder
    uv_fs_mkdir(uv_default_loop(), new uv_fs_t, FILE_STRUCTURE[0], 0755, [] (uv_fs_t* req) -> void {
        if (req->result && req->result != UV_EEXIST) {
            Core::Error(uv_strerror((int)req->result));
            delete req;
            return;
        }

        // iterate and try to load all provided resources
        for (auto resource : resources) {
            FS::Read(std::string(FILE_STRUCTURE[0]) + DS + resource + DS + FILE_STRUCTURE[1], [] (FS::result_t* result) -> void {
                tinyxml2::XMLDocument doc;
                doc.Parse(result->content, result->length);

                tinyxml2::XMLElement* meta = doc.FirstChildElement("meta");

                if (!meta) {
                    Core::Error("There is no <meta> tag inside your %.*s file.", result->fplength, result->filepath);
                    return;
                }

                if (!meta->FirstChildElement("somestuff")) {
                    Core::Error("no stufs");
                    return;
                }

                const char* title = meta->FirstChildElement("somestuff")->GetText();
                printf( "Name of play (1): %s\n", title );
            });
        }

        delete req;
    });
}

Resource::Manager::~Manager()
{

}

void Resource::Manager::Init()
{
}
