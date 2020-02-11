#include "CollisionComponent.h"
#include "src/engine/common/system/CollisionSystem.h"

CollisionComponent::CollisionComponent() :
    m_callback(nullptr)
{

}

CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::setCollisionCallback(std::function<void(Collision)> func) {
    m_callback = func;
}
