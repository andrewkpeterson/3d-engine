#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "System.h"

class CollisionSystem : public System
{
public:
    CollisionSystem(std::shared_ptr<GameWorld> gameworld);
    ~CollisionSystem() override;
};

#endif // COLLISIONSYSTEM_H
