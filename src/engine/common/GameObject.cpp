#include "GameObject.h"

GameObject::GameObject()
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

void GameObject::removeComponent(std::string name) {
    m_components.erase(name);
}

/*
std::shared_ptr<Component> GameObject::getComponent(std::string name) {
    return m_components.at(name);
}
*/

void GameObject::addComponentsToSystems()
{
    std::map<std::string, std::shared_ptr<Component>>::iterator it = m_components.begin();
    while (it != m_components.end()) {
        it->second->addSelfToSystems(m_gw);
        it++;
    }
}

void GameObject::removeComponentsFromSystems()
{
    std::map<std::string, std::shared_ptr<Component>>::iterator it = m_components.begin();
    while (it != m_components.end()) {
        it->second->removeSelfFromSystems(m_gw);
        it++;
    }
}

GameWorld *GameObject::getGameWorld()
{
    return m_gw;
}

