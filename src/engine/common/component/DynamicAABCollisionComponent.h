#ifndef DYNAMICAABCOLLISIONCOMPONENT_H
#define DYNAMICAABCOLLISIONCOMPONENT_H

#include "CollisionComponent.h"
#include "CylinderCollisionComponent.h"
#include "SphereCollisionComponent.h"
class StaticAABCollisionComponent;

class DynamicAABCollisionComponent : public CollisionComponent
{
public:
    DynamicAABCollisionComponent(bool can_move, bool active, glm::vec3 sides, int layer);
    ~DynamicAABCollisionComponent();

    void checkCollision(CollisionComponent *comp) override;
    void checkCollisionWithCylinder(CylinderCollisionComponent *that) override;
    void checkCollisionWithSphere(SphereCollisionComponent *comp) override;
    void checkCollisionWithDynamicAAB(DynamicAABCollisionComponent *comp) override;
    void checkCollisionWithStaticAAB(StaticAABCollisionComponent *that) override;

private:
    glm::vec3 m_sides;
};

#endif // DYNAMICAABCOLLISIONCOMPONENT_H
