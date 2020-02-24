#ifndef SPHERECOLLISIONCOMPONENT_H
#define SPHERECOLLISIONCOMPONENT_H

#include "CollisionComponent.h"
class CylinderCollisionComponent;
class StaticAABCollisionComponent;
class DynamicAABCollisionComponent;

class SphereCollisionComponent : public CollisionComponent
{
public:
    SphereCollisionComponent(bool can_move, float radius);
    ~SphereCollisionComponent() override;

    void checkCollision(CollisionComponent *comp) override;
    void checkCollisionWithCylinder(CylinderCollisionComponent *that) override;
    void checkCollisionWithSphere(SphereCollisionComponent *that) override;
    void checkCollisionWithDynamicAAB(DynamicAABCollisionComponent *taht) override;
    void checkCollisionWithStaticAAB(StaticAABCollisionComponent *that) override;

private:
    float m_radius;
};

#endif // SPHERECOLLISIONCOMPONENT_H
