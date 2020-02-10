#ifndef CYLINDERCOLLISIONCOMPONENT_H
#define CYLINDERCOLLISIONCOMPONENT_H

#include "Component.h"
#include "CollisionComponent.h"
#include "src/engine/common/system/CollisionSystem.h"

class CylinderCollisionComponent : public CollisionComponent
{
public:
    CylinderCollisionComponent(GameObject *gameworld, float radius, float height);
    ~CylinderCollisionComponent() override;
    void addGameObjectToSystems() override;
    void removeGameObjectFromSystems() override;

    void checkCollision(CollisionComponent *comp) override;
    void checkCollisionWithCylinder(CylinderCollisionComponent *comp) override;

private:
    float m_radius;
    float m_height;
};

#endif // CYLINDERCOLLISIONCOMPONENT_H
