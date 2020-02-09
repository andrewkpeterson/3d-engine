#include "Component.h"

Component::Component(std::shared_ptr<GameObject> gameobject) :
    m_gameobject(gameobject)
{

}

Component::~Component()
{

}
