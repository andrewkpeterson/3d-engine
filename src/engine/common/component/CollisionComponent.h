#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"

class GameWorld;

class CollisionComponent : public Component
{
public:
    CollisionComponent();
    ~CollisionComponent();
    void addObjectToGameWorldSystems(GameWorld *gw) override;
};

#endif // COLLISIONCOMPONENT_H
