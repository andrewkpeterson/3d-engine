#include "GameObject.h"

GameObject::GameObject(std::shared_ptr<GameWorld> gameworld) :
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

std::shared_ptr<GameWorld> GameObject::getGameWorld()
{
    return m_gw;
}
