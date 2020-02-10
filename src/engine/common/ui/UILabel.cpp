#include "UILabel.h"

UILabel::UILabel(std::string text, float size, glm::vec3 color, glm::vec2 pos, std::string matname) :
    m_text(text),
    m_size(size),
    m_color(color),
    m_pos(pos),
    m_matname(matname)

{
    g = Graphics::getGlobalInstance();
    m_material.color = m_color;
    g->addMaterial(m_matname, m_material);
}

UILabel::~UILabel()
{

}

void UILabel::drawSelf() {
    g->clearTransform();
    g->setMaterial(m_matname);
    g->translate(glm::vec3(m_pos.x, m_pos.y, 0.0f));
    g->drawText(m_text, m_size);
}
