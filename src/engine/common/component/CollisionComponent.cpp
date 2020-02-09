#include "CollisionComponent.h"
#include "src/engine/common/system/CollisionSystem.h"

CollisionComponent::CollisionComponent(std::shared_ptr<GameObject> gameobject) :
    Component(gameobject)
{

}

CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::tick(float seconds) {

}
