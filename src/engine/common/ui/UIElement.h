#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "UI.h"
#include "src/engine/common/component/UIComponent.h"
class UIComponent;

class UIElement
{
public:
    UIElement(UIComponent *component);
    ~UIElement();

    virtual void drawSelf() = 0;
    virtual void tick(float seconds) = 0;

protected:
    UIComponent *m_component;

};

#endif // UIELEMENT_H
