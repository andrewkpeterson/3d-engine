#ifndef PLATFORMERSTARTSCREEN_H
#define PLATFORMERSTARTSCREEN_H

#include "src/engine/common/Screen.h"

class PlatformerStartScreen : public Screen
{
public:
    PlatformerStartScreen(Application *parent);
    ~PlatformerStartScreen();

    void initializeGameWorld() override;
    void goToGameplay();
};

#endif // PLATFORMERSTARTSCREEN_H
