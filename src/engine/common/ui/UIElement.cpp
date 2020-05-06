#include "UIElement.h"
#include "src/engine/common/component/UIComponent.h"

UIElement::UIElement(UIComponent *component, std::string text) :
      m_component(component), should_draw(true), m_text(text)
{

}

UIElement::~UIElement()
{

}

void UIElement::setDraw(bool b) {
    should_draw = b;
}

void UIElement::setText(std::string str) {
    m_text = str;
}

std::string UIElement::getText() {
    return m_text;
}
