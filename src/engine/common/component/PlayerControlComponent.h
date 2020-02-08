#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class GameWorld;

/**
 * Controls the
 */
class PlayerControlComponent : public Component
{
public:
    PlayerControlComponent(std::shared_ptr<GameObject> gameobject);
    ~PlayerControlComponent() override;
    void addGameObjectToSystems() override;
    void removeGameObjectFromSystems() override;
};

#endif // PLAYERCONTROLCOMPONENT_H
