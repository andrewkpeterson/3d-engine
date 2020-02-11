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
    Component();
    virtual ~Component();
    virtual void addComponentToSystemsAndConnectComponents() = 0;
    virtual void removeComponentFromSystems() = 0;
    GameObject *getGameObject();
    void setGameObject(GameObject *obj);

protected:
    GameObject *m_gameobject;
};

#endif // COMPONENT_H
