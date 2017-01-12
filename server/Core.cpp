#include "stdinc.h"

namespace MOServer
{
    Core* Core::mInstance;

    Core::Core()
    {
        this->Init();
    }

    Core::~Core()
    {

    }

    /**
     * Main initialzing function
     */
    void Core::Init()
    {
        std::string test = "";

        test.append("==================================================\n");
        test.append("==                                              ==\n");
        test.append("==                  WUT                         ==\n");
        test.append("==                                              ==\n");
        test.append("==================================================\n");

        printf("%s\n\n", test.c_str());

        mRunning = true;
        mInstance = this;
    }

    /**
     * Main ticker function
     */
    void Core::Tick()
    {
        // std::cout << "tick tock\n";
    }

    /**
     * Return current isntance of the core
     * @return Core*
     */
    Core* Core::Instance()
    {
        return mInstance;
    }
}
