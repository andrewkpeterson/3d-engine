#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "System.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/component/CameraComponent.h"

class DrawSystem : public System<DrawableComponent>
{
public:
    DrawSystem(GameWorld *gameworld);
    ~DrawSystem() override;

    void addComponent(DrawableComponent *component);
    void removeComponent(DrawableComponent *component);

    void draw(Graphics *g);

private:
    Graphics *g;
};

#endif // DRAWSYSTEM_H
