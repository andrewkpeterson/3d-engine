#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>
#include <vector>
#include <map>
#include <unordered_set>

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

#include "src/engine/common/GameObject.h"
#include "src/engine/common/system/System.h"
#include "src/engine/util/TypeMap.h"

#include "src/engine/util/CommonIncludes.h"

class Graphics;
class System;
class Screen;


/**
 * A GameWorld is controlled by a Screen. The initial Systems and GameObjects of a
 * Screen are created in the game-defined Screen subclass' constructor.
 */
class GameWorld
{
public:
    GameWorld(Screen *screen);
    ~GameWorld();

    //TYPE MAP METHODS
    template <typename Sys>
    void addSystem(std::shared_ptr<Sys> &&c) {
      m_systems.put<Sys>(std::forward<std::shared_ptr<Sys>>(c));
    }

    template <typename Sys>
    void removeSystem() {
        m_systems.remove<Sys>();
    }

    template <typename Sys>
    std::shared_ptr<Sys> getSystem() {
        auto it = m_systems.find<Sys>();
        assert(it != m_systems.end());
        return std::dynamic_pointer_cast<Sys>(it->second);
    }

    void tick(float seconds);
    void draw(Graphics *g);
    void resize(int width, int height);
    void addGameObject(std::shared_ptr<GameObject> object); // adds a game object to the gameworld, and calls addToSystems on all of its components
    void removeGameObject(std::shared_ptr<GameObject> object);

    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void onKeyRepeated(QKeyEvent *event);
    void onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    void onMouseDragged(int deltaX, int deltaY);
    void onWheelEvent(QWheelEvent *event);

private:
    Screen* m_screen;
    std::unordered_set<std::shared_ptr<GameObject>> m_gameobjects;
    TypeMap<std::shared_ptr<System>> m_systems;
};

#endif // GAMEWORLD_H
