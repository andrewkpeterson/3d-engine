#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>
#include <vector>
#include <map>
#include <unordered_set>

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
    GameWorld();
    ~GameWorld();

    void tick();
    void draw(Graphics *g);

    template <typename Sys>
    void addSystem(std::shared_ptr<Sys> &&c) {
      m_systems.put<Sys>(std::forward<std::shared_ptr<Sys>>(c));
    }

    template <typename Sys>
    void removeSystem() {
        m_systems.remove<Sys>();
    }

    //void addSystem(std::shared_ptr<System> system);

    //void removeSystem(std::shared_ptr<System> system);
    void addGameObject(std::shared_ptr<GameObject> object); // adds a game object to the gameworld, and calls addToSystems on all of its components
    void removeGameObject(std::shared_ptr<GameObject> object);

    template <typename Sys>
    Sys* getSystem() {
        auto it = m_systems.find<Sys>();
        assert(it != m_systems.end());
        return static_cast<Sys*>(it->second.get());
    }

    //std::shared_ptr<System> getSystem(std::string name);

private:
    Screen* m_screen;
    std::unordered_set<std::shared_ptr<GameObject>> m_gameobjects;
    TypeMap<std::shared_ptr<System>> m_systems;
    //std::map<std::string, std::shared_ptr<System>> m_systems;

};

#endif // GAMEWORLD_H
