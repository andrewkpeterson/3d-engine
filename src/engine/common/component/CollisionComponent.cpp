#include "CollisionComponent.h"
#include "src/engine/common/system/CollisionSystem.h"

CollisionComponent::CollisionComponent(GameObject *gameobject) :
    Component(gameobject)
{

}

CollisionComponent::~CollisionComponent()
{

}

std::vector<Collision> CollisionComponent::getCollisions() {
    return m_collisions;
}

void CollisionComponent::clearCollisions() {
    m_collisions.clear();
}

void CollisionComponent::addCollision(Collision collision) {
    m_collisions.push_back(collision);
}

void CollisionComponent::setCollisionCallback(std::function<void(Collision)> func) {
    m_callback = func;
}
