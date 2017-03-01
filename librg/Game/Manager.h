#ifndef __game_manager
#define __game_manager

#include <Utils/Singleton.h>
#include "Handler.h"

#include "Objects/Entity.h"
#include "Objects/Player.h"
#include "Objects/Vehicle.h"

namespace Server::Game {
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
        // todo(inlife): change to std::array
        Game::Objects::Player* mPlayers[MAX_ENTITIES];
        Game::Objects::Vehicle* mVehicles[MAX_ENTITIES];
        Game::Handler* mHandler;
    };


}

#endif // __game_manager
