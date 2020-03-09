#include "DungeonStartScreen.h"

DungeonStartScreen::DungeonStartScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonStartScreen::~DungeonStartScreen()
{

}

void DungeonStartScreen::initializeGameWorld() {
    Graphics *g = Graphics::getGlobalInstance();

    g->addFont("press_start_2p", ":/fonts/PressStart2P-Regular.ttf");

}
