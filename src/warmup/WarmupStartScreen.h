#ifndef WARMUPSTARTSCREEN_H
#define WARMUPSTARTSCREEN_H

#include "src/engine/graphics/Graphics.h"
#include "src/engine/graphics/Camera.h"
#include "src/engine/common/Application.h"
#include "src/warmup/WarmupApplication.h"
#include "src/engine/common/Screen.h"

class WarmupStartScreen : public Screen
{
public:
    WarmupStartScreen(WarmupApplication *parent_app);
    ~WarmupStartScreen() override;

    void initializeGameWorld() override;

};

#endif // WARMUPSTARTSCREEN_H
