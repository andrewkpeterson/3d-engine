#ifndef SWORDCOMPONENT_H
#define SWORDCOMPONENT_H

#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/TickComponent.h"

class SwordComponent : public TickComponent
{
public:
    SwordComponent();
    ~SwordComponent();
    void tick(float seconds) override;
    void swing();
};

#endif // SWORDCOMPONENT_H
