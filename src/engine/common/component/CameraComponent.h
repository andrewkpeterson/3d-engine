#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"

class CameraComponent : public Component
{
public:
    CameraComponent(std::shared_ptr<GameObject> gameobject);
    ~CameraComponent();
    void addGameObjectToSystems() override;
    void removeGameObjectFromSystems() override;
};

#endif // CAMERACOMPONENT_H
