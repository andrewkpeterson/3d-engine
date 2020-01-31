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
    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void onMouseDragged(QKeyEvent *event);
    void onMousePressed(QKeyEvent *event);
    void onMouseReleased(QKeyEvent *event);
    void onWheelEvent(QKeyEvent *event);

protected:
    std::map<std::string, std::shared_ptr<Screen>> m_screenmap;
    std::shared_ptr<Screen> m_current_screen;

};

#endif // APPLICATION_H
