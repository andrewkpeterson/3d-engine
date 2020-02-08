#include "CollisionComponent.h"
#include "src/engine/common/system/CollisionSystem.h"

CollisionComponent::CollisionComponent(std::shared_ptr<GameObject> gameobject) :
    Component("CollisionComponent", gameobject)
{

}

CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::addGameObjectToSystems() {
    m_gameobject->getGameWorld()->getSystem<CollisionSystem>()->addComponent(getSharedPtr());
}

void CollisionComponent::removeGameObjectFromSystems() {
    m_gameobject->getGameWorld()->getSystem<CollisionSystem>()->removeComponent(getSharedPtr());
}
