#ifndef WARMUPSTARTSCREEN_H
#define WARMUPSTARTSCREEN_H

#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/Application.h"
#include "src/engine/common/Screen.h"

class WarmupStartScreen : public Screen
{
public:
    WarmupStartScreen();
    ~WarmupStartScreen() override;

    void tick(float seconds) override;
    void draw(Graphics *g) override;
};

#endif // WARMUPSTARTSCREEN_H
