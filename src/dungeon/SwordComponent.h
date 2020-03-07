#ifndef SWORDCOMPONENT_H
#define SWORDCOMPONENT_H

#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/TickComponent.h"

class SwordComponent : public TickComponent
{
public:
    SwordComponent();
    ~SwordComponent() override;
    void tick(float seconds) override;
    void swing();

private:
    bool swinging;
    bool forward;
    const float TIME_OF_SWING = 1;
};

#endif // SWORDCOMPONENT_H
