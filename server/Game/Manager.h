#ifndef _mo_game_manager
#define _mo_game_manager

#include "Handler.h"
#include "Entity.h"
#include "Player.h"
#include "Vehicle.h"

namespace M2OServer {
namespace Game  {

const entityId_t MAX_ENTITIES = 1000;

class Manager
{
public:
    Manager();
    ~Manager();

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
} // M2OServer

#endif // _mo_game_manager
