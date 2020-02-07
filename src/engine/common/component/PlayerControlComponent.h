#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class GameWorld;

class PlayerControlComponent : public Component
{
public:
    PlayerControlComponent();
    ~PlayerControlComponent() override;
    void addSelfToSystems(GameWorld *gw) override;
    void removeSelfFromSystems(GameWorld *gw) override;
};

#endif // PLAYERCONTROLCOMPONENT_H
