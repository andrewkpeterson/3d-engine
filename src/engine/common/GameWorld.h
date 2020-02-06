#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>
#include <vector>

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
    void addSystem(std::shared_ptr<System> system); // what should this take in??
    void removeSystem(std::string name); // what should this take in??
    void addGameObject(std::shared_ptr<GameObject> object); // what should this take in
    void removeGameObject(std::string name); // what should this take in??

private:
    std::vector<Screen*> m_screens; // reference to screens that control this GameWorld
    std::vector<std::shared_ptr<GameObject>> m_gameobjects;
    std::vector<std::shared_ptr<System>> m_systems;

};

#endif // GAMEWORLD_H
