#include "System.h"

System::System(std::string str) :
    name(str)
{

}

System::~System()
{

}

void System::tick() {

}

void System::addComponent(Component *component) {
    m_components.insert(component);
}

void System::removeComponent(Component *component) {
    m_components.erase(component);
}

const std::string System::getName() {
    return name;
}
