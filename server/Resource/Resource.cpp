#include <Scripting/Index.hpp>
#include <Core.h>
#include "Resource.h"

using namespace Server::Resource;

Resource::Resource(std::string name, std::vector<script_t*> scripts)
    : mVM(nullptr)
    , mName(name)
    , mScripts(scripts)
    , mRunning(false)
{
    this->Start();
}

/**
 * Start this resource
 * @return [description]
 */
bool Resource::Start()
{
    if (this->mRunning) {
        Core::Error("Cannot start resource, its already running!");
        return false;
    }

    Core::Log("Starting resource '%s'!", mName.c_str());

    // setup data
    mRunning = true;
    mVM      = sq_open(1024);

    // load all scripting bindings
    Scripting::Index::Install(mVM);

    // iterate over each script and start it
    // and clean up filename string pointer
    for (auto script : mScripts) {
        if (script->type != tServer) continue;

        try {
            Sqrat::Script vscript = Sqrat::Script(mVM);
            vscript.CompileFile(script->filename->c_str());
            vscript.Run();
        } catch( Exception e ) {
            Core::Error("Script loading exception: ");
        }

        delete script->filename;
    }

    return true;
}

bool Resource::Stop()
{
    if (!this->mRunning) {
        Core::Error("Cannot stop resource, its already stopped!");
        return false;
    }

    Core::Log("Stopping resource '%s'!", mName.c_str());

    sq_close(mVM);

    return (mRunning = false);
}

Resource::~Resource()
{
    if (this->mRunning) {
        this->Stop();
    }
}
