#include "DungeonGameplayScreen.h"
#include "src/engine/common/map/MapGenerator.h"

DungeonGameplayScreen::DungeonGameplayScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonGameplayScreen::~DungeonGameplayScreen()
{

}

void DungeonGameplayScreen::initializeGameWorld() {
    std::shared_ptr<MapSegment> map = MapGenerator::createMap(506);
}
