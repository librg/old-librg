#ifndef _m2o_core
#define _m2o_core

#include <Singleton.h>
#include <Utils.h>
#include "Network/Manager.h"
#include "Game/Manager.h"

namespace M2OServer {

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
    void Tick(int64_t tick);
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


} // namespace M2OServer


#endif // _m2o_core
