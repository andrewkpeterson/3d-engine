#ifndef WARMUPGAMEPLAYSCREEN_H
#define WARMUPGAMEPLAYSCREEN_H

#include "src/engine/graphics/Graphics.h"

class WarmupGameplayScreen
{
public:
    WarmupGameplayScreen();
    ~WarmupGameplayScreen();

    virtual void tick(float dt);
    virtual void draw(Graphics &g);
};

#endif // WARMUPGAMEPLAYSCREEN_H
