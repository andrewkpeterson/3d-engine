#ifndef COMPONENT_H
#define COMPONENT_H

#include "src/engine/util/CommonIncludes.h"

class GameObject;
class GameWorld;

class Component
{
public:
    Component(std::string str);
    virtual ~Component();
    virtual void addSelfToSystems(GameWorld *gw) = 0;
    virtual void removeSelfFromSystems(GameWorld *gw) = 0;
    const std::string getName();

protected:
    std::shared_ptr<GameObject> m_gameobject;
    const std::string name;
};

#endif // COMPONENT_H
