#include <Core.h>
#include "Resource.h"

using namespace Server::Resource;

Resource::Resource(std::string name, std::vector<script_t*> scripts)
    : mVM(nullptr)
    , mName(name)
    , mScripts(scripts)
{
    Core::Log("Creating resource '%s'!", mName.c_str());
}

Resource::~Resource()
{

}
