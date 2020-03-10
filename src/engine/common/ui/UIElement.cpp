#include "UIElement.h"
#include "src/engine/common/component/UIComponent.h"

UIElement::UIElement(UIComponent *component) :
    m_component(component)
{

}

UIElement::~UIElement()
{

}
