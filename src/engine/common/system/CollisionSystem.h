#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "System.h"
#include "src/engine/common/component/CollisionComponent.h"

class CollisionSystem : public System
{
public:
    CollisionSystem(std::shared_ptr<GameWorld> gameworld);
    ~CollisionSystem() override;

    void addComponent(CollisionComponent *component);
    void removeComponent(CollisionComponent *component);

    void tick(float seconds);

private:
    std::unordered_set<CollisionComponent*> m_components;

};

#endif // COLLISIONSYSTEM_H
