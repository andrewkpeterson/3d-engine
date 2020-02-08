#include "CameraComponent.h"
#include "src/engine/common/system/CameraSystem.h"

CameraComponent::CameraComponent(std::shared_ptr<GameObject> gameobject, glm::vec3 pos, glm::vec3 look) :
    Component("CameraComponent", gameobject),
    m_initial_pos(pos),
    m_initial_look(look),
    m_camera(std::make_shared<Camera>())
{
    m_camera->setEye(m_initial_pos);
    m_camera->setLook(m_initial_look);
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::addGameObjectToSystems()
{
    m_gameobject->getGameWorld()->getSystem<CameraSystem>()->addComponent(getSharedPtr());
}

void CameraComponent::removeGameObjectFromSystems() {
    m_gameobject->getGameWorld()->getSystem<CameraSystem>()->removeComponent(getSharedPtr());
}

std::shared_ptr<Camera> CameraComponent::getCamera() {
    return m_camera;
}
