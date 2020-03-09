#ifndef DUNGEONSTARTSCREEN_H
#define DUNGEONSTARTSCREEN_H

#include "src/engine/common/Application.h"
#include "src/engine/common/Screen.h"

class DungeonStartScreen : public Screen
{
public:
    DungeonStartScreen(Application *parent);
    ~DungeonStartScreen();

    void initializeGameWorld() override;
};

#endif // DUNGEONSTARTSCREEN_H
