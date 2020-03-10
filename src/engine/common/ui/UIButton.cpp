#include "UIButton.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/system/UISystem.h"
#include "src/engine/common/component/UIControllerComponent.h"

UIButton::UIButton(UIComponent *component, glm::vec2 pos, std::string text, std::string font, glm::vec3 size, float font_size,
                   std::string font_matname, std::string background_matname, std::function<void()> callback) :
    UIElement(component),
    m_pos(pos),
    m_text(text),
    m_font(font),
    m_size(size),
    m_font_size(font_size),
    m_font_matname(font_matname),
    m_backround_matname(background_matname),
    m_callback(callback)
{
    g = Graphics::getGlobalInstance();
}

UIButton::~UIButton()
{

}

void UIButton::tick(float seconds) {
    if (checkClicked()) {
        m_callback();
    }
}

void UIButton::drawSelf() {
    g->clearTransform();
    g->setMaterial(m_backround_matname);
    g->translate(glm::vec3(m_pos.x, m_pos.y, 0.0f));
    g->scale(glm::vec3(m_size.x,m_size.y,1.0));
    g->drawShape("uiquad");
    g->setMaterial(m_font_matname);
    g->clearTransform();
    g->translate(glm::vec3(m_pos.x, m_pos.y, 0.0f));
    g->drawText(m_font, m_text, m_font_size);
}

bool UIButton::checkClicked() {
    std::shared_ptr<UIControllerComponent> controller = m_component->getGameObject()->getGameWorld()->
                                                        getSystem<UISystem>()->getController();
    glm::vec3 mouse_pos = controller->getGameObject()->getComponent<TransformComponent>()->getPos();
    if (mouse_pos.x >= m_pos.x && mouse_pos.x <= m_pos.x + m_size.x) {
        if (mouse_pos.y >= m_pos.y && mouse_pos.y <= m_pos.y + m_size.y) {
            if (controller->getMousePressed()) {
                return true;
            }
        }
    }
}
