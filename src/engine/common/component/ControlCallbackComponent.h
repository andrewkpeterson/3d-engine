#ifndef CONTROLCALLBACKCOMPONENT_H
#define CONTROLCALLBACKCOMPONENT_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

class ControlCallbackComponent
{
public:
    ControlCallbackComponent();
    ~ControlCallbackComponent();

    virtual void onKeyPressed(QKeyEvent *event);
    virtual void onKeyReleased(QKeyEvent *event);
    virtual void onKeyRepeated(QKeyEvent *event);
    virtual void onMousePressed(QMouseEvent *event);
    virtual void onMouseReleased(QMouseEvent *event);
    virtual void onMouseDragged(int deltaX, int deltaY);
    virtual void onWheelEvent(QWheelEvent *event);
};

#endif // CONTROLCALLBACKCOMPONENT_H
