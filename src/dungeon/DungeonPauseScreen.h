#ifndef DUNGEONPAUSESCREEN_H
#define DUNGEONPAUSESCREEN_H

#include "src/engine/common/Application.h"
#include "src/engine/common/Screen.h"

class DungeonPauseScreen : public Screen
{
public:
    DungeonPauseScreen(Application *parent);
    ~DungeonPauseScreen();

    void initializeGameWorld() override;
};

#endif // DUNGEONPAUSESCREEN_H
