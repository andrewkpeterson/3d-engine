#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H

#include "ControlCallbackComponent.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/Screen.h"

class GameWorld;

class PlayerControlComponent : public ControlCallbackComponent
{
public:
    PlayerControlComponent(std::shared_ptr<GameObject> gameobject);
    ~PlayerControlComponent() override;
    void addGameObjectToSystems() override;
    void removeGameObjectFromSystems() override;

    void draw(Graphics *g);
    void tick(float seconds) override;

    void onKeyPressed(QKeyEvent *event) override;
    void onKeyReleased(QKeyEvent *event) override;
    void onKeyRepeated(QKeyEvent *event) override;
    void onMousePressed(QMouseEvent *event) override;
    void onMouseReleased(QMouseEvent *event) override;
    void onMouseDragged(int deltaX, int deltaY) override;
    void onWheelEvent(QWheelEvent *event) override;

private:
    const float MOUSE_SENSITIVITY = .1f;
    const float WALK_SPEED = .1f;
    const float GRAVITY = -.25f;
    const float JUMP_SPEED = .15f;
    bool off_ground;
    float y_vel;
};

#endif // PLAYERCONTROLCOMPONENT_H
