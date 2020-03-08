#ifndef ORTHOGRAPHICUITEXTCOMPONENT_H
#define ORTHOGRAPHICUITEXTCOMPONENT_H

#include "DrawableComponent.h"
#include "src/engine/graphics/Graphics.h"
#include "OrthographicUIComponent.h"

class OrthographicUITextComponent : public OrthographicUIComponent
{
public:
    OrthographicUITextComponent(std::string text, std::string matname, Material material, glm::vec3 offset, float size);
    OrthographicUITextComponent(std::string text, std::string matname, glm::vec3 offset, float size);
    ~OrthographicUITextComponent();
    void drawSelf(std::shared_ptr<Camera> camera) override;

private:
    std::string m_text;
    float m_size;
};

#endif // ORTHOGRAPHICUITEXTCOMPONENT_H
