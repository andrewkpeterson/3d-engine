#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "System.h"

class CameraComponent;

/**
 * The CameraSystem contains all the objects with cameras in the GameWorld.
 * The DrawSystem renders using the current camera of the camera system.
 */
class CameraSystem : public System
{
public:
    CameraSystem(std::shared_ptr<GameWorld> gameworld);
    ~CameraSystem();

    void setCurrCamComponent(std::shared_ptr<CameraComponent>);
    std::shared_ptr<CameraComponent> getCurrCamComponent();

private:
    std::shared_ptr<CameraComponent> m_currcam;
};

#endif // CAMERASYSTEM_H
