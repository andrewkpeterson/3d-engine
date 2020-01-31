#ifndef WARMUPGAMEPLAYSCREEN_H
#define WARMUPGAMEPLAYSCREEN_H

#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/Application.h"
#include "src/engine/common/Screen.h"
#include "src/engine/graphics/Camera.h"

class WarmupGameplayScreen : public Screen
{
public:
    WarmupGameplayScreen(Graphics *g);
    virtual ~WarmupGameplayScreen() override;

    void tick(float seconds) override;
    void draw(Graphics *g) override;

    void onKeyRepeated(QKeyEvent *event) override {}
    void onMousePressed(QMouseEvent *event) override {}
    void onMouseReleased(QMouseEvent *event) override {}
    void onMouseDragged(int deltaX, int deltaY) override;
    void onWheelEvent(QWheelEvent *event) override {}

    void resize(int w, int h) override;

    void restart();

private:
    std::shared_ptr<Camera> m_camera;

    const float MOUSE_SENSITIVITY = .1;
    const float WALK_SPEED = .1;
};

#endif // WARMUPGAMEPLAYSCREEN_H
