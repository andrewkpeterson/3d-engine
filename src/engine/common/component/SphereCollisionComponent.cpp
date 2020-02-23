#include "SphereCollisionComponent.h"
#include "TransformComponent.h"

SphereCollisionComponent::SphereCollisionComponent(bool can_move, float radius) :
    CollisionComponent (can_move),
    m_radius(radius)
{

}

SphereCollisionComponent::~SphereCollisionComponent()
{

}

void SphereCollisionComponent::checkCollision(CollisionComponent *comp) {
    comp->checkCollisionWithSphere(this);
}

void SphereCollisionComponent::checkCollisionWithAAB(AABCollisionComponent *comp) {

}

void SphereCollisionComponent::checkCollisionWithSphere(SphereCollisionComponent *that) {
    glm::vec3 this_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();

}

void SphereCollisionComponent::checkCollisionWithCylinder(CylinderCollisionComponent *comp) {

}
