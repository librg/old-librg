#include <tinyxml2.h>
#include <vector>

#include <librg/Core.h>
#include <librg/Utils/Filesystem.h>
#include <librg/Resource/Manager.h>

using namespace tinyxml2;
using namespace Server::Resource;

// TODO(inlife): move to config.xml!
std::vector<std::string> resources = {
    "resource-default",
    // "default",
};

std::unordered_map<std::string, scriptType> scriptTypes = {
    std::make_pair<std::string, scriptType>("server", tServer),
    std::make_pair<std::string, scriptType>("client", tClient),
    std::make_pair<std::string, scriptType>("shared", tShared),
};

Manager::Manager()
{
    // try to create resources folder
    int result = fs::mkdir("resources");

    if (result != 0 && result != UV_EEXIST) {
        Core::Error(uv_strerror((int)result));
        return;
    }

    // iterate and try to load all provided resources
    for (auto resource : resources) {
        fs::read(fs::path("resources", resource, "meta.xml"), [resource] (fs::result_t* result) -> void {
			tinyxml2::XMLDocument doc;

            doc.Parse(result->content, result->length);
            XMLElement* meta = doc.FirstChildElement("meta");

            if (!meta) {
                Core::Error("There is no <meta> tag inside your %.*s file.", result->fplength, result->filepath);
                return;
            }

            XMLElement * element = meta->FirstChildElement("script");
            std::vector<script_t*> scripts;

            // iterate over each script and add to the array
            while (element != nullptr)
            {
                // read up script type, and skip if nothing is loaded
                const char * scriptType = nullptr;
                scriptType = element->Attribute("type");
                if (scriptType == nullptr) continue;

                script_t* script = new script_t;

                // fill up data
                script->filename = new std::string(fs::path("resources", resource, std::string(element->GetText())));

                script->type = (scriptTypes.find(scriptType) == scriptTypes.end()) ? tServer : scriptTypes[scriptType];

                scripts.push_back(script);

                // goto next item in list
                element = element->NextSiblingElement("script");
            }

            Manager::Instance()->Add(resource, new Resource(resource, scripts));
        });
    }
}

Manager::~Manager()
{
    
}
