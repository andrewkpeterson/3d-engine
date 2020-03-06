#ifndef MULTISHAPEDRAWABLECOMPONENT_H
#define MULTISHAPEDRAWABLECOMPONENT_H


#include "Component.h"
#include "DrawableComponent.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/graphics/Graphics.h"

class MultiShapeDrawableComponent : public DrawableComponent
{
public:
    MultiShapeDrawableComponent(std::vector<std::string> geometry, std::vector<std::string> matname,
                                std::vector<bool> should_draw_comp);
    ~MultiShapeDrawableComponent() override;
    virtual void drawSelf() override;

private:
    std::vector<std::string> m_matnames;
    std::vector<std::string> m_shapes;
    std::vector<bool> m_should_draw_comp;

};

#endif // MULTISHAPEDRAWABLECOMPONENT_H
