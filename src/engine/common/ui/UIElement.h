#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "UI.h"
#include "src/engine/common/component/UIComponent.h"
class UIComponent;

class UIElement
{
public:
    UIElement(UIComponent *component, std::string text);
    ~UIElement();

    virtual void drawSelf() = 0;
    virtual void tick(float seconds) = 0;
    void setDraw(bool b);
    void setText(std::string);
    std::string getText();

protected:
    UIComponent *m_component;
    bool should_draw;
    std::string m_text;
};

#endif // UIELEMENT_H
