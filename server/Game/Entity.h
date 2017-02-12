#ifndef __game_entity
#define __game_entity

#include <Shared/Math/Math.hpp>

namespace Server {
namespace Game     {

typedef unsigned short world_t;
typedef unsigned short entityId_t;

class Entity {
public:
    Entity();
    ~Entity();


private:
    Vector3 mPosition;
    Vector3 mRotation;
    world_t mWorld;
};


} // namespace Game
} // namespace Server

#endif // __game_entity
