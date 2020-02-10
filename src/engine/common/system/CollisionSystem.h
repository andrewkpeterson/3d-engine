#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "System.h"

class CollisionComponent;
class CylinderCollisionComponent;

class CollisionSystem : public System
{
public:
    CollisionSystem(GameWorld *gameworld);
    ~CollisionSystem() override;

    void addComponent(CollisionComponent *component);
    void removeComponent(CollisionComponent *component);

    void checkForCollisions(float seconds);

private:
    std::unordered_set<CollisionComponent*> m_components;

};

#endif // COLLISIONSYSTEM_H
