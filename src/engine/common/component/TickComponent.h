#ifndef TICKCOMPONENT_H
#define TICKCOMPONENT_H

#include "Component.h"

class TickComponent : public Component
{
public:
    TickComponent();
    virtual ~TickComponent();
    virtual void tick(float seconds) = 0;
    virtual void addComponentToSystemsAndConnectComponents() override;
    virtual void removeComponentFromSystems() override;
};

#endif // TICKCOMPONENT_H
