#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include <map>

#include "src/engine/common/component/Component.h"

class Component;
class GameWorld;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::string name);
    std::shared_ptr<Component> getComponent(std::string name);
    void addComponentsToSystems();
    void removeComponentsFromSystems();
    GameWorld *getGameWorld();

private:
    std::map<std::string, std::shared_ptr<Component>> m_components;
    GameWorld *m_gw;

};

#endif // GAMEOBJECT_H
