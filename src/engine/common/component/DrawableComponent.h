#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/graphics/Graphics.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent(std::string geometry, std::string matname, Material material);
    ~DrawableComponent() override;
    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;
    void drawSelf();
    void setDraw(bool draw);

private:
    Material m_material;
    std::string m_matname;
    std::string m_geometry;
    bool shouldDraw;
    Graphics *g;
};

#endif // DRAWABLECOMPONENT_H
