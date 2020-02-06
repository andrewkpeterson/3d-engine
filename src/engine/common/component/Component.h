#ifndef COMPONENT_H
#define COMPONENT_H

#include "src/engine/util/CommonIncludes.h"

class GameObject;
class GameWorld;

class Component
{
public:
    Component();
    virtual ~Component();
    virtual void addObjectToGameWorldSystems(GameWorld *gw) = 0; // must change system

protected:
    GameObject *m_gameobject;
};

#endif // COMPONENT_H
