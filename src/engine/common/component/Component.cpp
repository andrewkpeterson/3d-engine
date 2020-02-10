#include "Component.h"

Component::Component(GameObject *gameobject) :
    m_gameobject(gameobject)
{

}

Component::~Component()
{

}

GameObject *Component::getGameObject() {
    return m_gameobject;
}
