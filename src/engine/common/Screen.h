#ifndef SCREEN_H
#define SCREEN_H

#include <QKeyEvent>
#include <map>

#include "src/engine/graphics/Graphics.h"

class Screen
{
public:
    Screen();
    virtual ~Screen();

    virtual void tick(float seconds) = 0;
    virtual void draw(Graphics *g) = 0;

    virtual void onKeyPressed(QKeyEvent *event);
    virtual void onKeyReleased(QKeyEvent *event);
    virtual void onMousePressed(QKeyEvent *event);
    virtual void onMouseReleased(QKeyEvent *event);
    virtual void onMouseDragged(QKeyEvent *event) = 0;
    virtual void onWheelEvent(QKeyEvent *event) = 0;

protected:
    std::map<std::string, bool> m_controlstates;
};

#endif // SCREEN_H
