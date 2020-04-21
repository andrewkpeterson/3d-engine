#ifndef PLATFORMERPLAYERCONTROLCOMPONENT_H
#define PLATFORMERPLAYERCONTROLCOMPONENT_H

#include "src/engine/common/component/ControlCallbackComponent.h"

struct Collision;

class PlatformerPlayerControlComponent : public ControlCallbackComponent
{
public:
    PlatformerPlayerControlComponent();
    ~PlatformerPlayerControlComponent();
    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;

    void tick(float seconds) override;
    void updateMovement(float seconds);
    void shoot(float seconds);
    void handleCollisionResolutionAndResponse(Collision collision);

    void onKeyPressed(QKeyEvent *event) override;
    void onKeyReleased(QKeyEvent *event) override;
    void onKeyRepeated(QKeyEvent *event) override;
    void onMousePressed(QMouseEvent *event) override;
    void onMouseReleased(QMouseEvent *event) override;
    void onMouseDragged(int deltaX, int deltaY) override;
    void onWheelEvent(QWheelEvent *event) override;

private:
    const float MOUSE_SENSITIVITY = .1f;
    float WALK_SPEED = .3f;
    const float GRAVITY = -50.0f;
    const float JUMP_SPEED = 20.0f;
    const float Y_MOVE_EPSILON = .02;

    const float PLAYER_BULLET_SPEED = 100;

    const float TOTAL_DODGE_TIME = .3;
    const float TOTAL_DODGE_RECHARGE_TIME = 2.0;
    bool dodging;
    float saved_dodge_time;
    float saved_dodge_recharge_time;


    int frames_since_last_collision;
    glm::vec3 last_normal;
    std::vector<float> heights;
    bool on_ground;
    bool can_jump;
    float y_vel;
    float distance_last_fallen;
    bool use_third_person;
    float third_person_cam_pos;
    int m_deltaX;
    int m_deltaY;
    const float MIN_CAM_TRANSLATION = 5.0f;
    const float MAX_CAM_TRANSLATION = 40.0f;
};

#endif // PLATFORMERPLAYERCONTROLCOMPONENT_H
