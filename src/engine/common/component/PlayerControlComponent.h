#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H

#include "ControlCallbackComponent.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/Screen.h"

class GameWorld;

class PlayerControlComponent : public ControlCallbackComponent
{
public:
    PlayerControlComponent(GameObject *gameobject);
    ~PlayerControlComponent() override;
    void addComponentToSystems() override;
    void removeComponentFromSystems() override;

    void tick(float seconds) override;
    void update(float seconds);
    void handleCollisionResolutionAndResponse();

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
    const float GRAVITY = -5.0f;
    const float JUMP_SPEED = 5.0f;
    const float GROUND_LEVEL = 0.0f;
    bool off_ground;
    bool can_jump;
    float y_vel;
    float distance_last_fallen;
    bool use_third_person;
    float third_person_cam_pos;
    const float MIN_CAM_TRANSLATION = 5.0f;
    const float MAX_CAM_TRANSLATION = 10.0f;

};

#endif // PLAYERCONTROLCOMPONENT_H
