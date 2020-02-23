#ifndef CYLINDERCOLLISIONCOMPONENT_H
#define CYLINDERCOLLISIONCOMPONENT_H

#include "Component.h"
#include "CollisionComponent.h"
#include "src/engine/common/system/CollisionSystem.h"
#include "SphereCollisionComponent.h"

class CylinderCollisionComponent : public CollisionComponent
{
public:
    CylinderCollisionComponent(bool can_move, float radius, float height);
    ~CylinderCollisionComponent() override;

    void checkCollision(CollisionComponent *comp) override;
    void checkCollisionWithCylinder(CylinderCollisionComponent *comp) override;
    void checkCollisionWithSphere(SphereCollisionComponent *comp) override;
    void checkCollisionWithAAB(AABCollisionComponent *comp) override;

    float getHeight();
    float getRadius();

private:
    float m_radius;
    float m_height;
};

#endif // CYLINDERCOLLISIONCOMPONENT_H
