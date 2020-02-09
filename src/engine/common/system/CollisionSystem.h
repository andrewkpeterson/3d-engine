#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "System.h"

class CollisionSystem : public System
{
public:
    CollisionSystem(std::shared_ptr<GameWorld> gameworld);
    ~CollisionSystem() override;

    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::shared_ptr<Component> component);

private:

};

#endif // COLLISIONSYSTEM_H
