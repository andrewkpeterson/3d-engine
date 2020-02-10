#include "CameraSystem.h"

CameraSystem::CameraSystem(GameWorld *gameworld) :
    System(gameworld)
{
}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::addComponent(CameraComponent *component) {
    m_components.insert(component);
}

void CameraSystem::removeComponent(CameraComponent *component) {
    m_components.erase(component);
}

void CameraSystem::setCurrentMainCameraComponent(CameraComponent *component) {
    m_main = component;
}

CameraComponent *CameraSystem::getCurrentMainCameraComponent() {
    return m_main;
}

void CameraSystem::resizeCameras(int width, int height) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        CameraComponent *comp = *it;
        comp->resizeCamera(width, height);
        it++;
    }
}
