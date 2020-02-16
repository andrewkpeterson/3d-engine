#include "DungeonGameplayScreen.h"
#include "src/engine/common/map/Map.h"

DungeonGameplayScreen::DungeonGameplayScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonGameplayScreen::~DungeonGameplayScreen()
{

}

void DungeonGameplayScreen::initializeGameWorld() {
    std::shared_ptr<Map> map = std::make_shared<Map>(504);
}
