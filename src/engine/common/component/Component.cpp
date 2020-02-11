#include "Component.h"

Component::Component() :
    m_gameobject()
{

}

Component::~Component()
{

}

GameObject *Component::getGameObject() {
    return m_gameobject;
}

void Component::setGameObject(GameObject *obj) {
    m_gameobject = obj;
}
