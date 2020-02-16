#ifndef DUNGEONGAMEPLAYSCREEN_H
#define DUNGEONGAMEPLAYSCREEN_H

#include "src/engine/common/Application.h"
#include "src/engine/common/Screen.h"
#include "src/engine/common/map/MapGenerator.h"

class DungeonGameplayScreen : public Screen
{
public:
    DungeonGameplayScreen(Application *parent);
    ~DungeonGameplayScreen() override;

    void initializeGameWorld() override;
};

#endif // DUNGEONGAMEPLAYSCREEN_H
