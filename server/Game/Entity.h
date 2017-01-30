#ifndef _m2o_game_entity
#define _m2o_game_entity

namespace M2OServer {
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
} // namespace M2OServer

#endif // _m2o_game_entity
