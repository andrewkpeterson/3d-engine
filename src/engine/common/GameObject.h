#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include "src/engine/util/TypeMap.h"

class Component;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::shared_ptr<Component> component);
    Component getComponent();

private:
    TypeMap<std::shared_ptr<Component>> m_components;

};

#endif // GAMEOBJECT_H
