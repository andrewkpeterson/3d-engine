#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(std::shared_ptr<GameWorld> gameworld) :
    System("CollisionSystem", gameworld)
{

}

CollisionSystem::~CollisionSystem()
{

}
