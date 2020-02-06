#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
    Component();
    ~Component();

protected:
    GameObject *m_gameobject;
};

#endif // COMPONENT_H
