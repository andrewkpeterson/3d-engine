#include "PlayerControlComponent.h"

PlayerControlComponent::PlayerControlComponent() :
    Component("PlayerControlComponent")
{

}

PlayerControlComponent::~PlayerControlComponent()
{

}

void PlayerControlComponent::addSelfToSystems(std::shared_ptr<GameWorld> gw)
{
    //gw->getSystem("TickSystem")->addComponent(this);
}

void PlayerControlComponent::removeSelfFromSystems(std::shared_ptr<GameWorld> gw) {
    //gw->getSystem("TickSystem")->addComponent(this);
}
