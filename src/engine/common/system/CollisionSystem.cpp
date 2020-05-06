#include "CollisionSystem.h"
#include "src/engine/common/component/CollisionComponent.h"

CollisionSystem::CollisionSystem(GameWorld *gameworld) :
      System(gameworld)
{
    for (int i = 0; i < NUM_LAYERS; i++) {
        m_layers.push_back(std::unordered_set<CollisionComponent*>());
        m_layers.push_back(std::unordered_set<CollisionComponent*>());
        m_layers.push_back(std::unordered_set<CollisionComponent*>());
    }
}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::addComponent(CollisionComponent *component) {
    int layer = component->getLayer();
    assert(layer == 0 || layer == 1 || layer == 2);
    m_layers[layer].insert(component);
}

void CollisionSystem::removeComponent(CollisionComponent *component) {
    int layer = component->getLayer();
    m_layers[layer].erase(component);
}

void CollisionSystem::checkForCollisions(float seconds) {


    for (int layer1_i = 0; layer1_i < NUM_LAYERS; layer1_i++) {
        for (int layer2_i = layer1_i + 1; layer2_i < NUM_LAYERS; layer2_i++) {
            const std::unordered_set<CollisionComponent*> &layer1 = m_layers[layer1_i];
            const std::unordered_set<CollisionComponent*> &layer2 = m_layers[layer2_i];
            for (auto i = layer1.begin(); i != layer1.end(); i++) {
                for (auto j = layer2.begin(); j != layer2.end(); j++) {
                    if (*j != *i) {
                        if (((*i)->isActive() && (*j)->isActive())) {
                            (*i)->checkCollision(*j);
                        }
                    }
                }
            }
        }
    }
}

