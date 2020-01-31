#ifndef WARMUPGAMEPLAYSCREEN_H
#define WARMUPGAMEPLAYSCREEN_H

#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/Application.h"
#include "src/engine/common/Screen.h"
#include "src/engine/graphics/Camera.h"

class WarmupGameplayScreen : public Screen
{
public:
    WarmupGameplayScreen();
    virtual ~WarmupGameplayScreen() override;

    void tick(float seconds) override;
    void draw(Graphics *g) override;

private:
    std::shared_ptr<Camera> m_camera;
};

#endif // WARMUPGAMEPLAYSCREEN_H
