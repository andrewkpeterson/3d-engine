#ifndef WARMUPSTARTSCREEN_H
#define WARMUPSTARTSCREEN_H

#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/Application.h"
#include "src/engine/common/Screen.h"

class WarmupStartScreen : public Screen
{
public:
    WarmupStartScreen();
    ~WarmupStartScreen() override;

    void tick(float seconds) override;
    void draw(Graphics *g) override;

    void onKeyRepeated(QKeyEvent *event) override {}
    void onMousePressed(QMouseEvent *event) override {}
    void onMouseReleased(QMouseEvent *event) override {}
    void onMouseDragged(int deltaX, int deltaY) override {};
    void onWheelEvent(QWheelEvent *event) override {}

    void resize(int w, int h) override;
};

#endif // WARMUPSTARTSCREEN_H
