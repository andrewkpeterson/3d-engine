#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include "System.h"
#include "src/engine/common/component/TickComponent.h"

class TickSystem : public System<TickComponent*>
{
public:
    TickSystem(GameWorld *gameworld);
    ~TickSystem() override;

    void addComponent(TickComponent *component);
    void removeComponent(TickComponent *component);

    void tick(float seconds);

};

#endif // TICKSYSTEM_H
