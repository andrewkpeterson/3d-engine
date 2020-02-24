#include "CollisionComponent.h"
#include "src/engine/common/system/CollisionSystem.h"

CollisionComponent::CollisionComponent(bool can_move) :
    m_callback(nullptr),
    m_can_move(can_move)
{

}

CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::setCollisionCallback(std::function<void(Collision)> func) {
    m_callback = func;
}

void CollisionComponent::addComponentToSystemsAndConnectComponents() {
    m_gameobject->getGameWorld()->getSystem<CollisionSystem>()->addComponent(this);
}

void CollisionComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<CollisionSystem>()->removeComponent(this);
}

void CollisionComponent::callCollisionCallback(Collision c) {
    m_callback(c);
}

bool CollisionComponent::hasCallback() {
    return m_callback != nullptr;
}

bool CollisionComponent::canMove() {
    return m_can_move;
}
