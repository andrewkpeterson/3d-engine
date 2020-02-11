#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include <functional>

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class CylinderCollisionComponent;
struct Collision;

class CollisionComponent : public Component
{
public:
    CollisionComponent();
    ~CollisionComponent() override;
    
    virtual void checkCollision(CollisionComponent *comp) = 0;
    virtual void checkCollisionWithCylinder(CylinderCollisionComponent *comp) = 0;
    void setCollisionCallback(std::function<void(Collision)> func);

protected:
    std::function<void(Collision)> m_callback;
};

struct Collision {
    CollisionComponent *collider;
    glm::vec3 half_mtv;
};

#endif // COLLISIONCOMPONENT_H
