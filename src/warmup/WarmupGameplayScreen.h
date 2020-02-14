#ifndef WARMUPGAMEPLAYSCREEN_H
#define WARMUPGAMEPLAYSCREEN_H

#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/Application.h"
#include "src/warmup/WarmupApplication.h"
#include "src/engine/common/Screen.h"
#include "src/engine/graphics/Camera.h"

#include "src/engine/common/system/CollisionSystem.h"
#include "src/engine/common/system/DrawSystem.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/ControlCallbackSystem.h"

class WarmupGameplayScreen : public Screen
{
public:
    WarmupGameplayScreen(Graphics *g, WarmupApplication *parent);
    virtual ~WarmupGameplayScreen() override;

    void initializeGameWorld() override;


private:

};

#endif // WARMUPGAMEPLAYSCREEN_H
