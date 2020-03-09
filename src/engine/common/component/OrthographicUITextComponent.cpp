#include "OrthographicUITextComponent.h"
#include "src/engine/graphics/Camera.h"
#include "TransformComponent.h"
#include "src/engine/common/system/OrthographicUISystem.h"

OrthographicUITextComponent::OrthographicUITextComponent(std::string text, std::string matname, Material material,
                                                         glm::vec3 offset, float size, std::string font) :
    OrthographicUIComponent(matname, material, offset),
    m_text(text),
    m_size(size),
    m_font(font)
{

}

OrthographicUITextComponent::OrthographicUITextComponent(std::string text, std::string matname, glm::vec3 offset,
                                                         float size, std::string font) :
    OrthographicUIComponent (matname, offset),
    m_text(text),
    m_size(size),
    m_font(font)
{

}

OrthographicUITextComponent::~OrthographicUITextComponent() {

}

void OrthographicUITextComponent::drawSelf(std::shared_ptr<Camera> camera) {
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    glm::vec3 screen_pos = convertToScreenSpace(t->getPos() + m_offset, camera);
    if (screen_pos.z > 0) {
        if (shouldDraw) {
            g->clearTransform();
            g->setMaterial(m_matname);
            g->translate(glm::vec3(screen_pos.x, screen_pos.y, screen_pos.z));
            g->drawText(m_font, m_text, m_size);
        }
    }
}
