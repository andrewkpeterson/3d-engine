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
class UI;


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
    template<class Sys>
    void addSystem(std::shared_ptr<Sys> &&c) {
      m_systems.put<Sys>(std::forward<std::shared_ptr<Sys>>(c));
    }

    template<typename Sys>
    void removeSystem() {
        m_systems.remove<Sys>();
    }

    template<typename Sys>
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
    void removeGameObject(std::string id);

    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void onKeyRepeated(QKeyEvent *event);
    void onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    void onMouseDragged(int deltaX, int deltaY);
    void onWheelEvent(QWheelEvent *event);

    void addUI(std::shared_ptr<UI>, std::string);
    std::shared_ptr<UI> getActiveUI();
    void setActiveUI(std::string);

    Screen *getScreen();
    std::shared_ptr<GameObject> getGameObjectByID(std::string id);
    void markGameObjectForDeletion(std::string id);
    void removeGameObjectsMarkedForDeletion();

private:
    Screen* m_screen;
    std::map<std::string, std::shared_ptr<GameObject>> m_gameobjects;
    TypeMap<std::shared_ptr<System>> m_systems;
    std::map<std::string, std::shared_ptr<UI>> m_uis;
    std::shared_ptr<UI> m_activeui;
    std::vector<std::string> ids_to_delete;
};

#endif // GAMEWORLD_H
