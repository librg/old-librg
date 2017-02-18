#include <Scripting/Index.hpp>
#include <Core.h>
#include "Resource.h"

using namespace Server::Resource;

Resource::Resource(std::string name, std::vector<script_t*> scripts)
    : mVM(nullptr)
    , mName(name)
    , mScripts(scripts)
{
    mVM = sq_open(1024);

    Scripting::Index::Install(mVM);

    for (auto script : scripts) {
        if (script->type != tServer) continue;

        try {
            Sqrat::Script vscript = Sqrat::Script(mVM);
        // Core::Log("loading script: %s", script->filename->c_str());
            // vscript.CompileString("::print(\"Hello world\");");
            vscript.CompileFile(script->filename->c_str());
            vscript.Run();
        } catch( Exception e ) {
            Core::Error("Script loading exception: ");
        }

        delete script->filename;
    }

    Core::Log("Creating resource '%s'!", mName.c_str());
}

Resource::~Resource()
{

}

void Resource::Unload()
{

}
