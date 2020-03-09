#include "UIButton.h"

UIButton::UIButton(glm::vec2 pos, std::string text, std::string font, glm::vec3 size, float font_size,
                   std::string font_matname, std::string background_matname, std::function<void()> callback) :
    m_pos(pos),
    m_text(text),
    m_font(font),
    m_size(size),
    m_font_size(font_size),
    m_font_matname(m_font_matname),
    m_backround_matname(background_matname),
    m_callback(callback)
{

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
    g->drawText(m_font, m_text, m_font_size);
    g->setMaterial(m_font_matname);
    g->scale(glm::vec3(m_size.x,m_size.y,1.0));
    g->drawShape("uiquad");
}

bool UIButton::checkClicked() {
    return false;
}
