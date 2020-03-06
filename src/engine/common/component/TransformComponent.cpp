#include "TransformComponent.h"

TransformComponent::TransformComponent(glm::vec3 pos, float scale) :
    Component(),
    m_pos(pos),
    roll(0),
    pitch(0),
    yaw(0),
    m_scale(scale),
    object_pos(glm::vec3(0,0,0)),
    object_yaw(0),
    object_pitch(0),
    object_roll(0)
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

void TransformComponent::setObjectSpaceOrientation() {
    g->translate(object_pos);
    g->rotate(object_yaw, glm::vec3(0,1,0));
    g->rotate(object_pitch, glm::vec3(1,0,0));
}

void TransformComponent::setObjectToWorldTransform() {
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

float TransformComponent::getYaw() {
    return yaw;
}

float TransformComponent::getRoll() {
    return roll;
}

float TransformComponent::getPitch() {
    return pitch;
}

void TransformComponent::setObjectPos(glm::vec3 pos) {
    object_pos = pos;
}

void TransformComponent::changeObjectYaw(float theta) {
    object_yaw += theta;
}

void TransformComponent::changeObjectRoll(float theta) {
    object_roll += theta;
}

void TransformComponent::changeObjectPitch(float theta) {
    object_pitch += theta;
}

void TransformComponent::setObjectYaw(float theta) {
    object_yaw = theta;
}

void TransformComponent::setObjectRoll(float theta) {
    object_roll = theta;
}

void TransformComponent::setObjectPitch(float theta) {
    object_pitch = theta;
}

float TransformComponent::getObjectYaw() {
    return object_yaw;
}

float TransformComponent::getObjectRoll() {
    return object_roll;
}

float TransformComponent::getObjectPitch() {
    return object_pitch;
}
