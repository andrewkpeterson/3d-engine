#include "GameObject.h"

int GameObject::nextID = 0;

GameObject::GameObject(GameWorld *gameworld, std::string id) :
    m_gw(gameworld)
{
    if (std::strcmp("", id.c_str()) == 0) {
        m_id = std::to_string(nextID);
        nextID++;
    } else {
        m_id = id;
    }
}

GameObject::~GameObject()
{

}

void GameObject::addSelfToSystems()
{
    auto it = m_components.begin();
    while (it != m_components.end()) {
        it->second->addComponentToSystems();
        it++;
    }
}

void GameObject::removeSelfFromSystems()
{
    auto it = m_components.begin();
    while (it != m_components.end()) {
        it->second->removeComponentFromSystems();
        it++;
    }
}

void GameObject::removeAllComponents() {
    m_components.clear();
}

GameWorld *GameObject::getGameWorld()
{
    return m_gw;
}

std::string GameObject::getID() {
    return m_id;
}
