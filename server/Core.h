#ifndef __core
#define __core

#define SERVER

#include <Network/Manager.h>
#include <Game/Manager.h>
#include <Scripting/Resource/Manager.h>

#include <Utils/Singleton.h>
#include <Utils/Utils.h>

namespace Server {

class Core : public Singleton<Core>
{
    friend class Singleton<Core>;

private:
    bool mRunning;

    Network::Manager* mNetworkManager;
    Game::Manager* mGameManager;

public:
    Core();
    ~Core();

    void Init();
    void Idle();
    void Tick(uint64_t tick);
    void OnInput(const char* message);

    static void Log(const char* format, ...);

    /**
     * Return if core is currently running
     * @return bool
     */
    bool IsRunning()
    {
        return mRunning;
    }
};


} // namespace Server


#endif // __core
