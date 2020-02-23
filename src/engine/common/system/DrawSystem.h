#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "System.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/component/CameraComponent.h"

class DrawSystem : public System
{
public:
    DrawSystem(GameWorld *gameworld);
    ~DrawSystem() override;

    void addComponent(DrawableComponent *component);
    void removeComponent(DrawableComponent *component);

    void draw(Graphics *g);

private:
    Graphics *g;
    std::unordered_set<DrawableComponent*> m_components;
};

#endif // DRAWSYSTEM_H
