#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include "System.h"

class TickSystem : public System
{
public:
    TickSystem(std::shared_ptr<GameWorld> gameworld);
    ~TickSystem() override;

    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::shared_ptr<Component> component);

    void tick(float seconds);
};

#endif // TICKSYSTEM_H
