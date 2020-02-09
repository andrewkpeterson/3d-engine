#include "TransformComponent.h"

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameobject, glm::vec3 pos, float scale) :
    Component(gameobject),
    m_pos(pos),
    m_scale(scale)
{
    g = Graphics::getGlobalInstance();
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::addGameObjectToSystems() {

}

void TransformComponent::removeGameObjectFromSystems() {

}

void TransformComponent::setObjectTransform() {
    g->scale(m_scale);
    // add in rotation later
    g->translate(m_pos);
}
