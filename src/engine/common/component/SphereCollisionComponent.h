#ifndef SPHERECOLLISIONCOMPONENT_H
#define SPHERECOLLISIONCOMPONENT_H

#include "CollisionComponent.h"
class CylinderCollisionComponent;
class StaticAABCollisionComponent;
class DynamicAABCollisionComponent;

class SphereCollisionComponent : public CollisionComponent
{
public:
    SphereCollisionComponent(bool can_move, bool active, float radius, int layer);
    ~SphereCollisionComponent() override;

    void checkCollision(CollisionComponent *comp) override;
    void checkCollisionWithCylinder(CylinderCollisionComponent *that) override;
    void checkCollisionWithSphere(SphereCollisionComponent *that) override;
    void checkCollisionWithDynamicAAB(DynamicAABCollisionComponent *that) override;
    void checkCollisionWithStaticAAB(StaticAABCollisionComponent *that) override;

    float getRadius();

private:
    float m_radius;
};

#endif // SPHERECOLLISIONCOMPONENT_H
