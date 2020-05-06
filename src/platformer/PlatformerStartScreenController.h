#ifndef PLATFORMERSTARTSCREENCONTROLLER_H
#define PLATFORMERSTARTSCREENCONTROLLER_H

#include "src/engine/common/component/TickComponent.h"

class PlatformerStartScreenController : public TickComponent
{
public:
    PlatformerStartScreenController();
    ~PlatformerStartScreenController();

    void tick(float seconds) override;
private:
    float saved_flash_time;
    const float TOTAL_FLASH_TIME = 1;
};

#endif // PLATFORMERSTARTSCREENCONTROLLER_H
