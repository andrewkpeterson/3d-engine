#ifndef CONTROLCALLBACKCOMPONENT_H
#define CONTROLCALLBACKCOMPONENT_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

#include "TickComponent.h"

class ControlCallbackComponent : public TickComponent
{
public:
    ControlCallbackComponent(std::shared_ptr<GameObject> gameobject);
    ~ControlCallbackComponent();

    virtual void tick(float seconds) = 0;

    virtual void onKeyPressed(QKeyEvent *event) = 0;
    virtual void onKeyReleased(QKeyEvent *event) = 0;
    virtual void onKeyRepeated(QKeyEvent *event) = 0;
    virtual void onMousePressed(QMouseEvent *event) = 0;
    virtual void onMouseReleased(QMouseEvent *event) = 0;
    virtual void onMouseDragged(int deltaX, int deltaY) = 0;
    virtual void onWheelEvent(QWheelEvent *event) = 0;
};

#endif // CONTROLCALLBACKCOMPONENT_H
