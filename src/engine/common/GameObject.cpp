#include "GameObject.h"
#include "src/engine/common/component/TransformComponent.h"

int GameObject::nextID = 0;

GameObject::GameObject(std::string id)
{
    if (std::strcmp("", id.c_str()) == 0) {
        m_id = std::to_string(nextID);
        nextID++;
    } else {
        m_id = id;
    }
    addComponent<TransformComponent>(std::make_shared<TransformComponent>(glm::vec3(0,0,0), 1.0));
}

GameObject::~GameObject()
{

}

void GameObject::addSelfToSystems()
{
    auto it = m_components.begin();
    while (it != m_components.end()) {
        it->second->addComponentToSystemsAndConnectComponents();
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

void GameObject::setGameWorld(GameWorld *gameworld)
{
    m_gw = gameworld;
}

std::string GameObject::getID() {
    return m_id;
}
