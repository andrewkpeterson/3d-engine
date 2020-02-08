#include "Component.h"

Component::Component(std::string str, std::shared_ptr<GameObject> gameobject) :
    name(str),
    m_gameobject(gameobject)
{

}

Component::~Component()
{

}

const std::string Component::getName()
{
    return name;
}
