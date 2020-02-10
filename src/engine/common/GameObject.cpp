#include "GameObject.h"

GameObject::GameObject(GameWorld *gameworld) :
    m_gw(gameworld)
{

}

GameObject::~GameObject()
{

}

void GameObject::addSelfToSystems()
{
    auto it = m_components.begin();
    while (it != m_components.end()) {
        it->second->addGameObjectToSystems();
        it++;
    }
}

void GameObject::removeSelfFromSystems()
{
    auto it = m_components.begin();
    while (it != m_components.end()) {
        it->second->removeGameObjectFromSystems();
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
