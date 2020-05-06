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
    /**
     * This method is called when a component is added to the gameworld. This method also
     * allows components to interact with each other before the object is active in the gameworld.
     */
    virtual void addComponentToSystemsAndConnectComponents() = 0;
    virtual void removeComponentFromSystems() = 0;
    GameObject *getGameObject();
    void setGameObject(GameObject *obj);

protected:
    GameObject *m_gameobject;
};

#endif // COMPONENT_H
