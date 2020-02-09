#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include "System.h"
#include "src/engine/common/component/TickComponent.h"

class TickSystem : public System
{
public:
    TickSystem(std::shared_ptr<GameWorld> gameworld);
    ~TickSystem() override;

    void addComponent(TickComponent *component);
    void removeComponent(TickComponent *component);

    void tick(float seconds);

private:
    std::unordered_set<TickComponent*> m_components;
};

#endif // TICKSYSTEM_H
