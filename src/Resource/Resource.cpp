#include <librg/core/shared.h>
#include <librg/scripting/scripting.hpp>
#include <librg/resource/resource.h>

using namespace librg;

Resource::Resource(std::string name, std::vector<script_t*> scripts)
    : mVM(nullptr)
    , mName(name)
    , mScripts(scripts)
    , mRunning(false)
{
    // TODO: move to later
    this->Start();
}

Resource::~Resource()
{
    if (this->mRunning) {
        this->Stop();
    }
}

/**
 * Start this resource
 * @return [description]
 */
bool Resource::Start()
{
    if (this->mRunning) {
        core::error("Cannot start resource, its already running!");
        return false;
    }

    core::log("Starting resource '%s'!", mName.c_str());

    // setup data
    mRunning = true;
    mVM      = sq_open(1024);

    // load all scripting bindings
    scripting::install(mVM);

    // iterate over each script and start it
    // and clean up filename string pointer
    for (auto script : mScripts) {
        if (script->type != tServer) continue;

        try {
            Sqrat::Script vscript = Sqrat::Script(mVM);
            vscript.CompileFile(script->filename->c_str());
            vscript.Run();
        } catch( Sqrat::Exception e ) {
            core::error("Script loading exception: %s", e.Message().c_str());
        }

        delete script->filename;
    }

    return true;
}

bool Resource::Stop()
{
    if (!this->mRunning) {
        core::error("Cannot stop resource, its already stopped!");
        return false;
    }

    core::log("Stopping resource '%s'!", mName.c_str());
    sq_close(mVM);

    return !(mRunning = false);
}
