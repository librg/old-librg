#ifndef __core
#define __core

#define SERVER

#include <librg/Event/Manager.h>
#include <librg/Entity/Manager.h>
#include <librg/Network/Manager.h>
#include <librg/Resource/Manager.h>

#include <librg/Utils/Singleton.h>
#include <librg/Utils/Utils.h>

namespace Server {

class Core : public Singleton<Core>
{
    friend class Singleton<Core>;

private:
    bool mRunning;

    Network::Manager* mNetworkManager;

public:
    Core();
    ~Core();

    void Init();
    void Idle();
    void Tick(uint64_t tick);
    void OnInput(const char* message);

    static void Log(const char* format, ...);
    static void Error(const char* format, ...);

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
