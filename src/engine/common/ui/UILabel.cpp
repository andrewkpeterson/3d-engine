#include "UILabel.h"

UILabel::UILabel(std::string text, float size, glm::vec3 color, glm::vec2 pos, std::string matname, std::string font) :
    m_text(text),
    m_size(size),
    m_color(color),
    m_pos(pos),
    m_matname(matname),
    m_font(font)

{
    g = Graphics::getGlobalInstance();
}

UILabel::~UILabel()
{

}

void UILabel::drawSelf() {
    g->clearTransform();
    g->setMaterial(m_matname);
    g->translate(glm::vec3(m_pos.x, m_pos.y, 0.0f));
    g->drawText(m_font, m_text, m_size);
}

void UILabel::setText(std::string str) {
    m_text = str;
}
