#include "CollisionSystem.h"
#include "src/engine/common/component/CollisionComponent.h"

CollisionSystem::CollisionSystem(GameWorld *gameworld) :
    System(gameworld)
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

void CollisionSystem::checkForCollisions(float seconds) {
    auto i = m_components.begin();
    while(i != m_components.end()) {
        CollisionComponent *comp1 = *i;
        auto j = i;
        j++;
        while (j != m_components.end()) {
            CollisionComponent *comp2 = *j;
            // only check for a collision if both are active
            if ((comp1->isActive() && comp2->isActive())) {
                comp1->checkCollision(comp2);
            }
            j++;
        }

        i++;
    }
}

