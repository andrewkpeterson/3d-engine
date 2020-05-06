#include "TickSystem.h"
#include "src/engine/common/GameWorld.h"
#include <omp.h>

TickSystem::TickSystem(GameWorld *gameworld) :
    System(gameworld)
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

//#pragma omp parallel num_threads(8)
    {
        for (auto it = m_components.begin(); it != m_components.end(); it++) {
            //#pragma omp single nowait
            {
                (*it)->tick(seconds);
            }
        }
    }
}
