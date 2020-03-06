#ifndef PRIMITIVEDRAWABLECOMPONENT_H
#define PRIMITIVEDRAWABLECOMPONENT_H

#include "Component.h"
#include "DrawableComponent.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/graphics/Graphics.h"

class PrimitiveDrawableComponent : public DrawableComponent
{
public:
    PrimitiveDrawableComponent(std::string geometry, std::string matname, Material material);
    PrimitiveDrawableComponent(std::string geometry, std::string matname);
    ~PrimitiveDrawableComponent() override;
    virtual void drawSelf() override;

private:
    std::string m_matname;
    std::string m_geometry;

};

#endif // PRIMITIVEDRAWABLECOMPONENT_H
