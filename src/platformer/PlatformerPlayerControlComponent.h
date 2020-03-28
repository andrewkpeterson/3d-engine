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
    void update(float seconds);
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
    float WALK_SPEED = .5f;
    const float GRAVITY = -50.0f;
    const float JUMP_SPEED = 20.0f;
    const float Y_MOVE_EPSILON = .02;
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
