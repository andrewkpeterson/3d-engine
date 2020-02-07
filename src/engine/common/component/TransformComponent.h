#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class GameWorld;

class TransformComponent : public Component
{
public:
    TransformComponent();
    ~TransformComponent();
    void addSelfToSystems(GameWorld *gw) override;
    void removeSelfFromSystems(GameWorld *gw) override;
};

#endif // TRANSFORMCOMPONENT_H
