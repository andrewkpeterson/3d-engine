#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class CollisionComponent : public Component
{
public:
    CollisionComponent(std::shared_ptr<GameObject> gameobject);
    ~CollisionComponent() override;
    virtual void tick(float seconds) = 0;
};

#endif // COLLISIONCOMPONENT_H
