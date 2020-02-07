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
class Component;

class System
{
public:
    System(std::string str);
    virtual ~System();

    virtual void tick();
    void addComponent(Component *component);
    void removeComponent(Component *component);
    const std::string getName();

protected:
    std::unordered_set<Component*> m_components;
    const std::string name;
};

#endif // SYSTEM_H
