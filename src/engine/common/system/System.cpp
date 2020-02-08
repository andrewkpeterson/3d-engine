#include "System.h"

System::System(std::string str, std::shared_ptr<GameWorld> gameworld) :
    m_gameworld(gameworld),
    name(str)
{

}

System::~System()
{

}

void System::tick() {

}

void System::addComponent(std::shared_ptr<Component> component) {
    m_components.insert(component);
}

void System::removeComponent(std::shared_ptr<Component> component) {
    m_components.erase(component);
}

const std::string System::getName() {
    return name;
}
