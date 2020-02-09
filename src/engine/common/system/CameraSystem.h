#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "System.h"
#include "src/engine/common/component/CameraComponent.h"

/**
 * The CameraSystem contains all the objects with cameras in the GameWorld.
 * The DrawSystem renders using the current camera of the camera system.
 */
class CameraSystem : public System
{
public:
    CameraSystem(std::shared_ptr<GameWorld> gameworld);
    ~CameraSystem();

    void addComponent(CameraComponent *component);
    void removeComponent(CameraComponent *component);

    void setCurrCamComponent(CameraComponent *component);
    CameraComponent *getCurrCamComponent();
    void resizeCameras(int width, int height);

private:
    std::unordered_set<CameraComponent*> m_components;
    CameraComponent *m_currcam;
};

#endif // CAMERASYSTEM_H
