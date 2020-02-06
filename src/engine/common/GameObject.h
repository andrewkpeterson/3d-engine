#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>

class Component;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void addComponent();
    void removeComponents();
    Component getComponent();

private:
    std::vector<std::shared_ptr<Component>> m_components;

};

#endif // GAMEOBJECT_H
