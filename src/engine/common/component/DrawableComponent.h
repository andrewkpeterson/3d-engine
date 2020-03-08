#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/graphics/Graphics.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent();
    virtual ~DrawableComponent() override;
    virtual void addComponentToSystemsAndConnectComponents() override;
    virtual void removeComponentFromSystems() override;
    virtual void drawSelf(std::shared_ptr<Camera> camera) = 0;
    void setDraw(bool draw);

protected:
    bool shouldDraw;
    Graphics *g;
};

#endif // DRAWABLECOMPONENT_H
