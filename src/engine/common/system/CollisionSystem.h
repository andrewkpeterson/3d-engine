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
    std::vector<std::unordered_set<CollisionComponent*>> m_layers;
    const int NUM_LAYERS = 3;
};

#endif // COLLISIONSYSTEM_H
