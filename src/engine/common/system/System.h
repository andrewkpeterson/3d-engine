#ifndef SYSTEM_H
#define SYSTEM_H

#include "src/engine/util/CommonIncludes.h"
#include "src/engine/util/TypeMap.h"
#include <memory>
#include <vector>
#include <unordered_set>

class Graphics;
class GameObject;
class GameWorld;
class Component;

template <class ComponentType>
class System
{
public:
    System(GameWorld *gameworld);
    virtual ~System();
Z
    void addComponent(ComponentType *component);
    void removeComponent(ComponentType *component);

protected:
    GameWorld *m_gameworld;
    std::unordered_set<ComponentType*> m_components;
};

#endif // SYSTEM_H
