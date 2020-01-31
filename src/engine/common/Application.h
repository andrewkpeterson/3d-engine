#ifndef APPLICATION_H
#define APPLICATION_H

#include <QKeyEvent>
#include <map>
#include <memory>

#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/Screen.h"

class Application
{
public:
    Application();
    virtual ~Application();

    virtual void tick(float seconds);
    virtual void draw(Graphics *g);

    void resize(int w, int h);

    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void onKeyRepeated(QKeyEvent *event);
    void onMouseDragged(int deltaX, int deltaY);
    void onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    void onWheelEvent(QWheelEvent *event);

protected:
    std::map<std::string, std::shared_ptr<Screen>> m_screenmap;
    std::shared_ptr<Screen> m_current_screen;

};

#endif // APPLICATION_H
