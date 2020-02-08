#include "CameraSystem.h"

CameraSystem::CameraSystem(std::shared_ptr<GameWorld> gameworld) :
    System("CameraSystem", gameworld)
{

}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::setCurrCamComponent(std::shared_ptr<CameraComponent> cam) {
    m_currcam = cam;
}

std::shared_ptr<CameraComponent> CameraSystem::getCurrCamComponent() {
    return m_currcam;
}
