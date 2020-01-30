#ifndef APPLICATION_H
#define APPLICATION_H

#include <QKeyEvent>
#include "src/engine/graphics/Graphics.h"

class Application
{
public:
    Application();
    virtual ~Application();

    virtual void tick(float dt);
    virtual void draw(Graphics &g);
    void onKeyPressed(QKeyEvent &event);
    void onKeyReleased(QKeyEvent &event);
    void onMouseDragged(QKeyEvent &event);
    void onMousePressed(QKeyEvent &event);
    void onMouseReleased(QKeyEvent &event);
    void onWheelEvent(QKeyEvent &event);

};

#endif // APPLICATION_H
