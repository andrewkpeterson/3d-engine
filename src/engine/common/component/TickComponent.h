#ifndef TICKCOMPONENT_H
#define TICKCOMPONENT_H

#include "Component.h"

class TickComponent : public Component
{
public:
    TickComponent();
    ~TickComponent();
    virtual void tick(float seconds) = 0;
};

#endif // TICKCOMPONENT_H
