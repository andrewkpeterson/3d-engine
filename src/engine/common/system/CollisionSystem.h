#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "System.h"

class CollisionComponent;
class CylinderCollisionComponent;

class CollisionSystem : public System<CollisionComponent*>
{
public:
    CollisionSystem(GameWorld *gameworld);
    ~CollisionSystem() override;

    void addComponent(CollisionComponent *component);
    void removeComponent(CollisionComponent *component);

    void checkForCollisions(float seconds);

};

#endif // COLLISIONSYSTEM_H
