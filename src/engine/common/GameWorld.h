#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>
#include <vector>
#include <map>
#include <unordered_set>

#include "src/engine/common/GameObject.h"
#include "src/engine/common/system/System.h"

#include "src/engine/util/CommonIncludes.h"

class Graphics;
class System;
class Screen;

class GameWorld
{
public:
    GameWorld();
    ~GameWorld();

    void tick();
    void draw(Graphics *g);
    void addSystem(std::shared_ptr<System> system);
    void removeSystem(std::shared_ptr<System> system);
    void addGameObject(std::shared_ptr<GameObject> object); // adds a game object to the gameworld, and calls addToSystems on all of its components
    void removeGameObject(std::shared_ptr<GameObject> object);
    std::shared_ptr<System> getSystem(std::string name);

private:
    std::map<std::string, Screen*> m_screens; // reference to screens that control this GameWorld
    std::unordered_set<std::shared_ptr<GameObject>> m_gameobjects;
    std::map<std::string, std::shared_ptr<System>> m_systems;

};

#endif // GAMEWORLD_H
