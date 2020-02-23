#ifndef CONTROLCALLBACKSYSTEM_H
#define CONTROLCALLBACKSYSTEM_H

#include "System.h"
#include "src/engine/common/component/ControlCallbackComponent.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

class ControlCallbackSystem : public System
{
public:
    ControlCallbackSystem(GameWorld *gameworld);
    ~ControlCallbackSystem() override;

    void addComponent(ControlCallbackComponent *component);
    void removeComponent(ControlCallbackComponent *component);

    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void onKeyRepeated(QKeyEvent *event);
    void onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    void onMouseDragged(int deltaX, int deltaY);
    void onWheelEvent(QWheelEvent *event);

private:
    std::unordered_set<ControlCallbackComponent*> m_components;
};

#endif // CONTROLCALLBACKSYSTEM_H
