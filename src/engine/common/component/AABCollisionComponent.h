#ifndef AABCOLLISIONCOMPONENT_H
#define AABCOLLISIONCOMPONENT_H

#include "CollisionComponent.h"
#include "CylinderCollisionComponent.h"
#include "SphereCollisionComponent.h"

struct AAB {
    glm::vec3 pos;
    glm::vec3 neg;
};

class AABCollisionComponent : public CollisionComponent
{
public:
    AABCollisionComponent(bool can_move, std::vector<AAB> &bounds);
    ~AABCollisionComponent() override;

    void checkCollision(CollisionComponent *comp) override;
    void checkCollisionWithCylinder(CylinderCollisionComponent *that) override;
    void checkCollisionWithSphere(SphereCollisionComponent *comp) override;
    void checkCollisionWithAAB(AABCollisionComponent *comp) override;

    // a AAB must be translated whenever its translate component changes
    void translate(glm::vec3 t);

private:
    std::vector<AAB> m_bounds;
};

#endif // AABCOLLISIONCOMPONENT_H
