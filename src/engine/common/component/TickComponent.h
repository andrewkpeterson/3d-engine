#ifndef TICKCOMPONENT_H
#define TICKCOMPONENT_H

#include "Component.h"

class TickComponent : public Component
{
public:
    TickComponent(std::string str, std::shared_ptr<GameObject> gameobject);
    ~TickComponent();
    virtual void tick() = 0;
};

#endif // TICKCOMPONENT_H
