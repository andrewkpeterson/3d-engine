#ifndef COMPONENT_H
#define COMPONENT_H

#include "src/engine/util/CommonIncludes.h"
#include "src/engine/graphics/Graphics.h"
#include <memory>

class GameObject;
class GameWorld;

class Component
{
public:
    Component(std::shared_ptr<GameObject> gameobject);
    virtual ~Component();
    virtual void addGameObjectToSystems() = 0;
    virtual void removeGameObjectFromSystems() = 0;
    const std::string getName();

protected:
    std::shared_ptr<GameObject> m_gameobject;
};

#endif // COMPONENT_H
