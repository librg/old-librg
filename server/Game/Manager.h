#ifndef __game_manager
#define __game_manager

#include <Utils/Singleton.h>
#include "Handler.h"
#include "Entity.h"
#include "Player.h"
#include "Vehicle.h"

namespace Server {
namespace Game  {

const entityId_t MAX_ENTITIES = 1000;

class Manager : public Singleton<Manager>
{
    friend class Singleton<Manager>;

public:
    Manager() = default;
    ~Manager() = default;

    void Init();
    inline void Trigger(short eventId, void* data)
    {
        mHandler->Dispatch(eventId, data);
    }

private:
    Game::Player* mPlayers[MAX_ENTITIES];
    Game::Vehicle* mVehicles[MAX_ENTITIES];
    Game::Handler* mHandler;
};


} // Game
} // Server

#endif // __game_manager
