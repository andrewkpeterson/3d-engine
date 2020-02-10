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

void CameraSystem::setCurrCamComponent(CameraComponent *component) {
    m_currcam = component;
}

CameraComponent *CameraSystem::getCurrCamComponent() {
    return m_currcam;
}

void CameraSystem::resizeCameras(int width, int height) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        //it is fine to cast here because we know that only Drawable components can add themselves to the Draw System
        CameraComponent *comp = *it;
        comp->resizeCamera(width, height);
        it++;
    }
}
