#include "UIShape.h"

UIShape::UIShape(UIComponent *component, std::string geometry, glm::vec2 pos, glm::vec2 size, std::string matname) :
    UIElement(component),
    m_geometry(geometry),
    m_pos(pos),
    m_size(size),
    m_matname(matname)
{
    g = Graphics::getGlobalInstance();
}

UIShape::~UIShape()
{

}

void UIShape::drawSelf() {
    g->clearTransform();
    g->setMaterial(m_matname);
    g->translate(glm::vec3(m_pos.x, m_pos.y, 0.0f));
    g->scale(glm::vec3(m_size.x,m_size.y,1.0));
    g->drawShape(m_geometry);
}
