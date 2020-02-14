#ifndef STARTCONTROLLER_H
#define STARTCONTROLLER_H

#include "src/engine/common/component/ControlCallbackComponent.h"

class StartControlComponent : public ControlCallbackComponent
{
public:
    StartControlComponent();
    ~StartControlComponent();

    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;

    void tick(float seconds) override {}

    void onKeyPressed(QKeyEvent *event) override {}
    void onKeyReleased(QKeyEvent *event) override {}
    void onKeyRepeated(QKeyEvent *event) override {}
    void onMousePressed(QMouseEvent *event) override;
    void onMouseReleased(QMouseEvent *event) override {}
    void onMouseDragged(int deltaX, int deltaY) override {}
    void onWheelEvent(QWheelEvent *event) override {}
};

#endif // STARTCONTROLLER_H
