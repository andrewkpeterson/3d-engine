#include "TransformComponent.h"

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameobject, glm::vec3 pos) :
    Component("TransformComponent", gameobject),
    m_pos(pos)
{

}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::addGameObjectToSystems()
{

}

void TransformComponent::removeGameObjectFromSystems() {

}

void TransformComponent::setObjectTransform() {

}
