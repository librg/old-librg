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
        this->Log("Destroying core...");
    }

    void Core::Log(const char* format, ...)
    {
        va_list ap;
        char message[1024] = { 0 };
        va_start(ap, format);
        vsprintf(message, format, ap);
        va_end(ap);

        // TODO(inlife): move to async trigger -> callback
        printf("[SERVER] [%s] - %s\n", Utils::currentDateTime().c_str(), message);
    }

    /**
     * Main initialzing function
     */
    void Core::Init()
    {
        std::string test = "";

        test.append("==================================================\n");
        test.append("==                                              ==\n");
        test.append("==                 ¯\\_(ツ)_/¯                   ==\n");
        test.append("==                                              ==\n");
        test.append("==================================================\n");

        printf("%s\n\n", test.c_str());

        mRunning = true;
        mInstance = this;
    }

    /**
     * Main ticker function
     */
    void Core::Tick(int64_t tick)
    {
        // this->Log("tick tock: %d", tick);
    }

    /**
     * Main idle function
     */
    void Core::Idle()
    {
        // this->Log("idle...");
    }
}
