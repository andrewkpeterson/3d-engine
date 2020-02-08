#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class GameWorld;

class PlayerControlComponent : public Component
{
public:
    PlayerControlComponent(std::shared_ptr<GameObject> gameobject);
    ~PlayerControlComponent() override;
    void addGameObjectToSystems() override;
    void removeGameObjectFromSystems() override;

    void draw(Graphics *g);
    void tick(float seconds);

    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void onKeyRepeated(QKeyEvent *event);
    void onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    void onMouseDragged(int deltaX, int deltaY);
    void onWheelEvent(QWheelEvent *event);

private:
    const float MOUSE_SENSITIVITY = .1f;
    const float WALK_SPEED = .1f;
    const float GRAVITY = -.25f;
    const float JUMP_SPEED = .15f;
    bool off_ground;
    float y_vel;
};

#endif // PLAYERCONTROLCOMPONENT_H
