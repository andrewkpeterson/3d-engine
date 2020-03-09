#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "UI.h"

class UIElement
{
public:
    UIElement();
    ~UIElement();

    virtual void drawSelf() = 0;
    virtual void tick(float seconds) = 0;

};

#endif // UIELEMENT_H
