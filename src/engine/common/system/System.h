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
    System(std::string str);
    virtual ~System();

    virtual void tick();
    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::shared_ptr<Component> component);
    const std::string getName();

protected:
    std::unordered_set<std::shared_ptr<Component>> m_components;
    std::shared_ptr<GameWorld> m_gw;
    const std::string name;
};

#endif // SYSTEM_H
