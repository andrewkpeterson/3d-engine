#ifndef SCREEN_H
#define SCREEN_H

#include <QKeyEvent>
#include "src/engine/graphics/Graphics.h"

class Screen
{
public:
    Screen();
    virtual ~Screen();

    virtual void tick(float dt);
    virtual void draw(Graphics &g);
    void onKeyPressed(QKeyEvent &event);
    void onKeyReleased(QKeyEvent &event);
    void onMouseDragged(QKeyEvent &event);
    void onMousePressed(QKeyEvent &event);
    void onMouseReleased(QKeyEvent &event);
    void onWheelEvent(QKeyEvent &event);
};

#endif // SCREEN_H
