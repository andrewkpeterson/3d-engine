#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

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
    std::vector<Component> m_components;

};

#endif // GAMEOBJECT_H
