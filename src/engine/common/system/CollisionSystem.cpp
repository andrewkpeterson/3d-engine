#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(std::shared_ptr<GameWorld> gameworld) :
    System("CollisionSystem", gameworld)
{

}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::addComponent(CollisionComponent *component) {
    m_components.insert(component);
}

void CollisionSystem::removeComponent(CollisionComponent *component) {
    m_components.erase(component);
}

void CollisionSystem::tick(float seconds) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        //it is fine to cast here because we know that only Drawable components can add themselves to the Draw System
        CollisionComponent *comp = *it;

        it++;
    }
}
