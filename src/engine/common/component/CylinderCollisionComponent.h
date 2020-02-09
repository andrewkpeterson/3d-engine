#ifndef CYLINDERCOLLISIONCOMPONENT_H
#define CYLINDERCOLLISIONCOMPONENT_H

#include "Component.h"
#include "CollisionComponent.h"
#include "src/engine/common/system/CollisionSystem.h"

class CylinderCollisionComponent : public CollisionComponent
{
public:
    CylinderCollisionComponent(std::shared_ptr<GameObject> gameworld);
    ~CylinderCollisionComponent() override;
    void addGameObjectToSystems() override;
    void removeGameObjectFromSystems() override;

};

#endif // CYLINDERCOLLISIONCOMPONENT_H
