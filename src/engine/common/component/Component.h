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
    Component(GameObject *gameobject);
    virtual ~Component();
    virtual void addGameObjectToSystems() = 0;
    virtual void removeGameObjectFromSystems() = 0;
    GameObject *getGameObject();

protected:
    GameObject *m_gameobject;
};

#endif // COMPONENT_H
