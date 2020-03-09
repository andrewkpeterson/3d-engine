#include "DungeonPauseScreen.h"

DungeonPauseScreen::DungeonPauseScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonPauseScreen::~DungeonPauseScreen()
{

}

void DungeonPauseScreen::initializeGameWorld() {
    Graphics *g = Graphics::getGlobalInstance();

    g->addFont("press_start_2p", ":/fonts/PressStart2P-Regular.ttf");

}
