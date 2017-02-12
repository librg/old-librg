#ifndef __game_entity
#define __game_entity

#include <Shared/Math/Math.hpp>
#include <Game/World.h>

namespace Server  {
namespace Game    {

typedef unsigned short entityId_t;

namespace Objects {

class Entity {
public:
    Entity();
    ~Entity();


private:
    Vector3 mPosition;
    Vector3 mRotation;
    Game::world_t mWorld;
};


} // namespace Objects
} // namespace Game
} // namespace Server

#endif // __game_entity
