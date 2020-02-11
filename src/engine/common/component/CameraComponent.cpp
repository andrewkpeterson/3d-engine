#include "CameraComponent.h"
#include "src/engine/common/system/CameraSystem.h"

CameraComponent::CameraComponent(glm::vec3 initial_pos, glm::vec3 initial_look) :
    Component(),
    m_initial_pos(initial_pos),
    m_initial_look(initial_look),
    m_camera(std::make_shared<Camera>())
{
    m_camera->setEye(m_initial_pos);
    m_camera->setLook(m_initial_look);
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<CameraSystem>()->addComponent(this);
}

void CameraComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<CameraSystem>()->removeComponent(this);
}

std::shared_ptr<Camera> CameraComponent::getCamera() {
    return m_camera;
}

void CameraComponent::resizeCamera(int width, int height) {
    m_camera->setScreenSize(glm::vec2(width, height));
}
