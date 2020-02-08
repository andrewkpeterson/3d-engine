#include "DrawSystem.h"

DrawSystem::DrawSystem(std::shared_ptr<GameWorld> gameworld) :
    System("DrawSystem", gameworld)
{

}

DrawSystem::~DrawSystem()
{

}

void DrawSystem::draw(Graphics *g) {

}

