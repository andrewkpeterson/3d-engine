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
    CameraSystem(GameWorld *gameworld);
    ~CameraSystem();

    void addComponent(CameraComponent *component);
    void removeComponent(CameraComponent *component);

    void setCurrentMainCameraComponent(CameraComponent *component);
    CameraComponent *getCurrentMainCameraComponent();
    void resizeCameras(int width, int height);

private:
    CameraComponent *m_main;
    std::unordered_set<CameraComponent*> m_components;
};

#endif // CAMERASYSTEM_H
