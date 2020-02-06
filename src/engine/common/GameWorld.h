#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>
#include <vector>
#include <map>

#include "src/engine/util/CommonIncludes.h"

class Graphics;
class System;
class GameObject;
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

private:
    std::map<std::string, Screen*> m_screens; // reference to screens that control this GameWorld
    std::vector<std::shared_ptr<GameObject>> m_gameobjects;
    std::vector<std::shared_ptr<System>> m_systems;

};

#endif // GAMEWORLD_H
