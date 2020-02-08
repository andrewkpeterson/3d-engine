#ifndef WARMUPGAMEPLAYSCREEN_H
#define WARMUPGAMEPLAYSCREEN_H

#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/Application.h"
#include "src/game/WarmupApplication.h"
#include "src/engine/common/Screen.h"
#include "src/engine/graphics/Camera.h"

#include "src/engine/common/system/CollisionSystem.h"
#include "src/engine/common/system/DrawSystem.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/ControlCallbackSystem.h"

class WarmupGameplayScreen : public Screen
{
public:
    WarmupGameplayScreen(Graphics *g, WarmupApplication *parent);
    virtual ~WarmupGameplayScreen() override;

    //void tick(float seconds) override;
    //void draw(Graphics *g) override;
    //void resize(int w, int h) override;
    //void restartApplication();
    //void restartScreen() override;
    void initializeGameWorld() override;

    //void onKeyRepeated(QKeyEvent *event) override {}
    //void onMousePressed(QMouseEvent *event) override {}
    //void onMouseReleased(QMouseEvent *event) override {}
    //void onMouseDragged(int deltaX, int deltaY) override;
    //void onWheelEvent(QWheelEvent *event) override {}

private:
    std::shared_ptr<Camera> m_camera;

    const float MOUSE_SENSITIVITY = .1f;
    const float WALK_SPEED = .1f;
    const float GRAVITY = -.25f;
    const float JUMP_SPEED = .15f;
    bool off_ground;
    float y_vel;
};

#endif // WARMUPGAMEPLAYSCREEN_H
