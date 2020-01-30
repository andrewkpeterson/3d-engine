#ifndef WARMUPSTARTSCREEN_H
#define WARMUPSTARTSCREEN_H

#include "src/engine/graphics/Graphics.h"

class WarmupStartScreen
{
public:
    WarmupStartScreen();
    ~WarmupStartScreen();

    virtual void tick(float dt);
    virtual void draw(Graphics &g);
};

#endif // WARMUPSTARTSCREEN_H
