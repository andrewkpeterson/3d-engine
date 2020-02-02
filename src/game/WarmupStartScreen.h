#ifndef WARMUPSTARTSCREEN_H
#define WARMUPSTARTSCREEN_H

#include "src/engine/graphics/Graphics.h"
#include "src/engine/graphics/Camera.h"
#include "src/engine/common/Application.h"
#include "src/game/WarmupApplication.h"
#include "src/engine/common/Screen.h"

class WarmupStartScreen : public Screen
{
public:
    WarmupStartScreen(Graphics *g, WarmupApplication *parent_app);
    ~WarmupStartScreen() override;

    void tick(float seconds) override;
    void draw(Graphics *g) override;
    void resize(int w, int h) override;
    void restartScreen() override;

    void onKeyRepeated(QKeyEvent *event) override {}
    void onMousePressed(QMouseEvent *event) override;
    void onMouseReleased(QMouseEvent *event) override {}
    void onMouseDragged(int deltaX, int deltaY) override {}
    void onWheelEvent(QWheelEvent *event) override {}

private:
    std::shared_ptr<Camera> m_camera;
};

#endif // WARMUPSTARTSCREEN_H
