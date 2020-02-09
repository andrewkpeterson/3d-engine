#include "TickSystem.h"

TickSystem::TickSystem(std::shared_ptr<GameWorld> gameworld) :
    System("TickSystem", gameworld)
{

}

TickSystem::~TickSystem()
{

}

void TickSystem::addComponent(TickComponent *component) {
    m_components.insert(component);
}

void TickSystem::removeComponent(TickComponent *component) {
    m_components.erase(component);
}

void TickSystem::tick(float seconds) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        TickComponent *comp = *it;
        comp->tick(seconds);
        it++;
    }
}
