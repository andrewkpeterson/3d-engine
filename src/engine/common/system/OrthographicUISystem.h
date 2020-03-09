#ifndef ORTHOGRAPHICUISYSTEM_H
#define ORTHOGRAPHICUISYSTEM_H

#include "System.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/OrthographicUIComponent.h"

class OrthographicUISystem : public System
{
public:
    OrthographicUISystem(GameWorld *gameworld);
    ~OrthographicUISystem() override;

    void addComponent(OrthographicUIComponent *component);
    void removeComponent(OrthographicUIComponent *component);
    void resizeCamera(int width, int height);
    void draw(Graphics *g);

private:
    Graphics *g;
    std::unordered_set<OrthographicUIComponent*> m_components;
    std::shared_ptr<Camera> orthographic_camera;
};
#endif // ORTHOGRAPHICUISYSTEM_H
