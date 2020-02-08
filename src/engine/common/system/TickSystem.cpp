#include "TickSystem.h"

TickSystem::TickSystem(std::shared_ptr<GameWorld> gameworld) :
    System("TickSystem", gameworld)
{

}

TickSystem::~TickSystem()
{

}

void TickSystem::tick(float seconds) {

}
