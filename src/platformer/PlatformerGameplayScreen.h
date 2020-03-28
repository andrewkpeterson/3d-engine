#ifndef PLATFORMERGAMEPLAYSCREEN_H
#define PLATFORMERGAMEPLAYSCREEN_H

#include "src/engine/common/Screen.h"

class PlatformerGameplayScreen : public Screen
{
public:
    PlatformerGameplayScreen(Application *parent);
    ~PlatformerGameplayScreen();

    void initializeGameWorld() override;
};

#endif // PLATFORMERGAMEPLAYSCREEN_H
