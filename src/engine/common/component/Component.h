#ifndef COMPONENT_H
#define COMPONENT_H

#include "src/engine/util/CommonIncludes.h"
#include <memory>

class GameObject;
class GameWorld;

class Component : public std::enable_shared_from_this<Component>
{
public:
    Component(std::string str, std::shared_ptr<GameObject> gameobject);
    virtual ~Component();
    virtual void addGameObjectToSystems() = 0;
    virtual void removeGameObjectFromSystems() = 0;
    const std::string getName();
    std::shared_ptr<Component> getSharedPtr() {
        return shared_from_this();
    }

protected:
    std::shared_ptr<GameObject> m_gameobject;
    const std::string name;
};

#endif // COMPONENT_H
