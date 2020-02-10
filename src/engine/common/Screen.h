#ifndef SCREEN_H
#define SCREEN_H

#include <QKeyEvent>
#include <map>

#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/GameWorld.h"

class Application;

/**
 * A screen handles its GameWorld and game-side subclasses can define behavior
 * for screens to receive information from other screens.
 *
 * The Systems and initial GameObjects in the GameWorld of the Screen are
 * initialized in the constructor of the game-defined subclasses of Screen.
 */
class Screen
{
public:
    Screen(Application *parent);
    virtual ~Screen();

    virtual void tick(float seconds);
    virtual void draw(Graphics *g);

    virtual void resize(int width, int height);
    virtual void setAppReadyToRestart();

    virtual void initializeGameWorld() = 0;

    virtual void onKeyPressed(QKeyEvent *event);
    virtual void onKeyReleased(QKeyEvent *event);
    virtual void onKeyRepeated(QKeyEvent *event);
    virtual void onMousePressed(QMouseEvent *event);
    virtual void onMouseReleased(QMouseEvent *event);
    virtual void onMouseDragged(int deltaX, int deltaY);
    virtual void onWheelEvent(QWheelEvent *event);

    virtual void restartScreen();

    Application *getApp();

protected:
    Application *m_app;
    std::shared_ptr<GameWorld> m_gameworld;
};

#endif // SCREEN_H
