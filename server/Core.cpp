#include <Core.h>

using namespace Server;

Core::Core()
    : mRunning(false)
    , mNetworkManager(nullptr)
    , mGameManager(nullptr)
    // , mDebugLogger(true, true)
{
    this->Init();
}

Core::~Core()
{
    // delete Network::Manager::Instance();
    // delete Game::Manager::Instance();
    // delete Resource::Manager::Instance();

    this->Log("stopping server...");
}

void Core::Log(const char* format, ...)
{
    va_list ap;
    char message[1024] = { 0 };
    va_start(ap, format);
    vsprintf(message, format, ap);
    va_end(ap);

    // TODO(inlife): move to async trigger -> callback
    printf("[SERVER][%s] - %s\n", Utils::currentDateTime().c_str(), message);

    // va_list args;
    // va_start(args, format);

    // Core::Instance()->GetLogger().WriteLn(format, args);

    // va_end(args);
}

void Core::Error(const char* format, ...)
{
    va_list ap;
    char message[1024] = { 0 };
    va_start(ap, format);
    vsprintf(message, format, ap);
    va_end(ap);

    // TODO(inlife): move to async trigger -> callback
    printf("[SERVER][%s][ERROR] - %s\n", Utils::currentDateTime().c_str(), message);
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

    Game::Manager::Instance();
    Network::Manager::Instance();
    Resource::Manager::Instance();

    mRunning  = true;
}

void Core::OnInput(const char* message)
{
    Core::Log("console: %s", message);
}

/**
 * Main ticker function
 */
void Core::Tick(uint64_t tick)
{
    Network::Manager::Instance()->Update(tick);
}

/**
 * Main idle function
 */
void Core::Idle()
{
    Network::Manager::Instance()->Receive();
}
