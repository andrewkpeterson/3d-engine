#ifndef CONTROLCALLBACKSYSTEM_H
#define CONTROLCALLBACKSYSTEM_H

#include "System.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

class ControlCallbackSystem : public System
{
public:
    ControlCallbackSystem(std::shared_ptr<GameWorld> gameworld);
    ~ControlCallbackSystem() override;

    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void onKeyRepeated(QKeyEvent *event);
    void onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    void onMouseDragged(int deltaX, int deltaY);
    void onWheelEvent(QWheelEvent *event);

private:

};

#endif // CONTROLCALLBACKSYSTEM_H
