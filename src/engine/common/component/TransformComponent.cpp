#include "TransformComponent.h"

TransformComponent::TransformComponent(glm::vec3 pos, float scale) :
    Component(),
    m_pos(pos),
    roll(0),
    pitch(0),
    yaw(0),
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
    g->translate(m_pos);
    g->scale(m_scale);
    g->rotate(yaw, glm::vec3(0,1,0));
    g->rotate(pitch, glm::vec3(1,0,0));
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

void TransformComponent::changeYaw(float theta) {
    m_heading.x = std::cos(theta) * m_heading.x - std::sin(theta) * m_heading.y;
    m_heading.y = std::sin(theta) * m_heading.x - std::cos(theta) * m_heading.y;
    yaw += theta;
}

void TransformComponent::changeRoll(float theta) {
    roll += theta;
}

void TransformComponent::changePitch(float theta) {
    pitch += theta;
}

void TransformComponent::setYaw(float theta) {
    yaw = theta;
}

void TransformComponent::setRoll(float theta) {
    roll = theta;
}

void TransformComponent::setPitch(float theta) {
    pitch = theta;
}

