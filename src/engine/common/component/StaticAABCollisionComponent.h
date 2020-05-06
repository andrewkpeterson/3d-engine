#ifndef AABCOLLISIONCOMPONENT_H
#define AABCOLLISIONCOMPONENT_H

#include "CollisionComponent.h"
#include "CylinderCollisionComponent.h"
#include "SphereCollisionComponent.h"

struct AAB {
    glm::vec3 pos;
    glm::vec3 neg;
};

class StaticAABCollisionComponent : public CollisionComponent
{
public:
    StaticAABCollisionComponent(bool can_move, bool active, std::vector<AAB> bounds, int layer);
    ~StaticAABCollisionComponent() override;

    void checkCollision(CollisionComponent *comp) override;
    void checkCollisionWithCylinder(CylinderCollisionComponent *that) override;
    void checkCollisionWithSphere(SphereCollisionComponent *that) override;
    void checkCollisionWithDynamicAAB(DynamicAABCollisionComponent *comp) override;
    void checkCollisionWithStaticAAB(StaticAABCollisionComponent *comp) override;

    // a static AAB must be translated whenever its translate component changes
    void translate(glm::vec3 t);

    const std::vector<AAB> &getBounds();
    void setBounds(std::vector<AAB> bounds);

private:
    // an AAB collision component can have multiple bounding boxes, because it might be a chunk with
    // multiple walls
    std::vector<AAB> m_bounds;
};

#endif // AABCOLLISIONCOMPONENT_H
