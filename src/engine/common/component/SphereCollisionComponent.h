#ifndef SPHERECOLLISIONCOMPONENT_H
#define SPHERECOLLISIONCOMPONENT_H

#include "CollisionComponent.h"
class CylinderCollisionComponent;
class AABCollisionComponent;

class SphereCollisionComponent : CollisionComponent
{
public:
    SphereCollisionComponent(bool can_move, float radius);
    ~SphereCollisionComponent() override;

    void checkCollision(CollisionComponent *comp) override;
    void checkCollisionWithCylinder(CylinderCollisionComponent *comp) override;
    void checkCollisionWithSphere(SphereCollisionComponent *that) override;
    void checkCollisionWithAAB(AABCollisionComponent *comp) override;

private:
    float m_radius;
};

#endif // SPHERECOLLISIONCOMPONENT_H
