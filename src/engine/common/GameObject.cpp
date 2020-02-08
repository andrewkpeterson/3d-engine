#include "GameObject.h"

GameObject::GameObject(std::shared_ptr<GameWorld> gameworld) :
    m_gw(gameworld)
{

}

GameObject::~GameObject()
{

}

/*
void GameObject::addComponent(std::shared_ptr<Component> component) {
    m_components[component->getName()] = component;
}
*/

/*
void GameObject::removeComponent(std::string name) {
    m_components.erase(name);
}
*/

/*
std::shared_ptr<Component> GameObject::getComponent(std::string name) {
    return m_components.at(name);
}
*/

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

