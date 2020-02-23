#include "TransformComponent.h"

TransformComponent::TransformComponent(glm::vec3 pos, float scale) :
    Component(),
    m_pos(pos),
    m_scale(scale)
{
    g = Graphics::getGlobalInstance();
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::addComponentToSystemsAndConnectComponents() {

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

void TransformComponent::setScale(float size)
{
    m_scale = size;
}

glm::vec3 TransformComponent::getPos()
{
    return m_pos;
}

