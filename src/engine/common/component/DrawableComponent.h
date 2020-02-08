#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/graphics/Graphics.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent(std::shared_ptr<GameObject> gameobject, std::string geometry,
                      std::string matname, Material material);
    ~DrawableComponent() override;
    void addGameObjectToSystems() override;
    void removeGameObjectFromSystems() override;
    void drawSelf();

private:
    Material m_material;
    std::string m_matname;
    std::string m_geometry;
    Graphics *g;

};

#endif // DRAWABLECOMPONENT_H
