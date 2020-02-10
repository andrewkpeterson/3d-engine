#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/graphics/Camera.h"

class CameraComponent : public Component
{
public:
    CameraComponent(GameObject *gameobject, glm::vec3 initial_pos, glm::vec3 initial_look);
    ~CameraComponent();
    void addGameObjectToSystems() override;
    void removeGameObjectFromSystems() override;
    std::shared_ptr<Camera> getCamera();
    void resizeCamera(int width, int height);

private:
    glm::vec3 m_initial_pos;
    glm::vec3 m_initial_look;
    std::shared_ptr<Camera> m_camera;
};

#endif // CAMERACOMPONENT_H
