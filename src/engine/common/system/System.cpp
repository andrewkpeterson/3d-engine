#include "System.h"

System::System(GameWorld *gameworld) :
    m_gameworld(gameworld)
{

}

System::~System()
{

}

void System::addComponent(ComponentType *component) {
    m_components.insert(component);
}

void System::removeComponent(ComponentType *component) {
    m_components.erase(component);
}
