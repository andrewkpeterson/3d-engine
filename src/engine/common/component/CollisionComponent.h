#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include <functional>

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class CylinderCollisionComponent;
class SphereCollisionComponent;
class StaticAABCollisionComponent;
class DynamicAABCollisionComponent;
struct Collision;

class CollisionComponent : public Component
{
public:
    CollisionComponent(bool can_move, bool active);
    virtual ~CollisionComponent() override;
    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;
    
    virtual void checkCollision(CollisionComponent *comp) = 0;
    virtual void checkCollisionWithCylinder(CylinderCollisionComponent *comp) = 0;
    virtual void checkCollisionWithStaticAAB(StaticAABCollisionComponent *comp) = 0;
    virtual void checkCollisionWithDynamicAAB(DynamicAABCollisionComponent *comp) = 0;
    virtual void checkCollisionWithSphere(SphereCollisionComponent *comp) = 0;
    void setCollisionCallback(std::function<void(Collision)> func);
    void callCollisionCallback(Collision c);
    bool hasCallback();
    bool canMove();
    bool isActive();
    void setActive(bool b);

protected:
    std::function<void(Collision)> m_callback;
    bool m_can_move;
    bool m_active;
};

struct Collision {
    CollisionComponent *collider;
    glm::vec3 half_mtv;
};

#endif // COLLISIONCOMPONENT_H
