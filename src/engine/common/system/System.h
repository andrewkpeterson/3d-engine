#ifndef SYSTEM_H
#define SYSTEM_H

#include "src/engine/util/CommonIncludes.h"
#include "src/engine/util/TypeMap.h"
#include <memory>
#include <vector>
#include <unordered_set>

class Graphics;
class System;
class GameObject;
class GameWorld;
class Component;

class System
{
public:
    System(std::string str, std::shared_ptr<GameWorld> gameworld);
    virtual ~System();

    virtual void tick();
    void addGameObject(std::shared_ptr<GameObject> gameobject);
    void removeGameObject(std::shared_ptr<GameObject> gameobject);
    const std::string getName();

protected:
    std::unordered_set<std::shared_ptr<GameObject>> m_gameobjects;
    std::shared_ptr<GameWorld> m_gameworld;
    const std::string name;
};

#endif // SYSTEM_H
