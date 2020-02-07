#ifndef APPLICATION_H
#define APPLICATION_H

#include <QKeyEvent>
#include <map>
#include <memory>

#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/Screen.h"

/**
 * The Application is in charge of creating screens and changing between them.
 * Information can be shared between screens using game-side methods.
 */
class Application
{
public:
    Application();
    virtual ~Application();

    virtual void tick(float seconds);
    virtual void draw(Graphics *g);
    void resize(int w, int h);
    void changeScreen(std::string screen_name);
    void addScreen(std::shared_ptr<Screen> screen, std::string name);
    void removeScreen(std::string name);
    virtual void restart();

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
    Graphics *m_graphics;
    int app_width;
    int app_height;

};

#endif // APPLICATION_H
