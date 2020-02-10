#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject *gameobject, glm::vec3 pos, float scale) :
    Component(gameobject),
    m_pos(pos),
    m_scale(scale)
{
    g = Graphics::getGlobalInstance();
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::addComponentToSystems() {

}

void TransformComponent::removeComponentFromSystems() {

}

void TransformComponent::setObjectTransform() {
    // add in rotation later
    g->translate(m_pos);
    g->scale(m_scale);
}

void TransformComponent::translate(glm::vec3 translation) {
    m_pos += translation;
}

void TransformComponent::setPos(glm::vec3 position)
{
    m_pos = position;
}

glm::vec3 TransformComponent::getPos()
{
    return m_pos;
}

