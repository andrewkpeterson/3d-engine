#include "CylinderCollisionComponent.h"

CylinderCollisionComponent::CylinderCollisionComponent(std::shared_ptr<GameObject> gameworld) :
    CollisionComponent(gameworld)
{

}

CylinderCollisionComponent::~CylinderCollisionComponent()
{

}

void CylinderCollisionComponent::addGameObjectToSystems() {
    m_gameobject->getGameWorld()->getSystem<CollisionSystem>()->addComponent(this);
}

void CylinderCollisionComponent::removeGameObjectFromSystems() {
    m_gameobject->getGameWorld()->getSystem<CollisionSystem>()->removeComponent(this);
}
