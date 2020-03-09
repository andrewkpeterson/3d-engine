#ifndef DUNGEONPAUSECONTROLCOMPONENT_H
#define DUNGEONPAUSECONTROLCOMPONENT_H

#include "src/engine/common/component/ControlCallbackComponent.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/Screen.h"

class DungeonPauseControlComponent : public ControlCallbackComponent
{
public:
    DungeonPauseControlComponent();
    ~DungeonPauseControlComponent();
    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;

    void onKeyPressed(QKeyEvent *event) override;
    void onKeyReleased(QKeyEvent *event) override;
    void onKeyRepeated(QKeyEvent *event) override;
    void onMousePressed(QMouseEvent *event) override;
    void onMouseReleased(QMouseEvent *event) override;
    void onMouseDragged(int deltaX, int deltaY) override;
    void onWheelEvent(QWheelEvent *event) override;
    void tick(float seconds) override;
};

#endif // DUNGEONPAUSECONTROLCOMPONENT_H
