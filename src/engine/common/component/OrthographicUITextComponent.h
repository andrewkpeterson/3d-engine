#ifndef ORTHOGRAPHICUITEXTCOMPONENT_H
#define ORTHOGRAPHICUITEXTCOMPONENT_H

#include "DrawableComponent.h"
#include "src/engine/graphics/Graphics.h"
#include "OrthographicUIComponent.h"

class UIElement;
class UILabel;

class OrthographicUITextComponent : public OrthographicUIComponent
{
public:
    OrthographicUITextComponent(std::string text, std::string matname, Material material, glm::vec3 offset, float size,
                                std::string font);
    OrthographicUITextComponent(std::string text, std::string matname, glm::vec3 offset, float size, std::string font);
    ~OrthographicUITextComponent();
    void drawSelf(std::shared_ptr<Camera> camera) override;

private:
    std::string m_text;
    float m_size;
    std::string m_font;
};

#endif // ORTHOGRAPHICUITEXTCOMPONENT_H
