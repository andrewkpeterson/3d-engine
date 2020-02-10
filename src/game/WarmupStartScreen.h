#ifndef WARMUPSTARTSCREEN_H
#define WARMUPSTARTSCREEN_H

#include "src/engine/graphics/Graphics.h"
#include "src/engine/graphics/Camera.h"
#include "src/engine/common/Application.h"
#include "src/game/WarmupApplication.h"
#include "src/engine/common/Screen.h"

class WarmupStartScreen : public Screen
{
public:
    WarmupStartScreen(Graphics *g, WarmupApplication *parent_app);
    ~WarmupStartScreen() override;

    void initializeGameWorld() override;

};

#endif // WARMUPSTARTSCREEN_H
