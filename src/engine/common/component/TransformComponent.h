#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class GameWorld;

class TransformComponent : public Component
{
public:
    TransformComponent();
    ~TransformComponent() override;
    void addSelfToSystems(std::shared_ptr<GameWorld> gw) override;
    void removeSelfFromSystems(std::shared_ptr<GameWorld> gw) override;
};

#endif // TRANSFORMCOMPONENT_H
