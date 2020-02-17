#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/graphics/Graphics.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent();
    ~DrawableComponent() override;
    virtual void addComponentToSystemsAndConnectComponents() override;
    virtual void removeComponentFromSystems() override;
    virtual void drawSelf() = 0;
    void setDraw(bool draw);

protected:
    bool shouldDraw;
    Graphics *g;
};

#endif // DRAWABLECOMPONENT_H
