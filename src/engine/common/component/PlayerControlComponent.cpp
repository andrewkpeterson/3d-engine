#include "PlayerControlComponent.h"

PlayerControlComponent::PlayerControlComponent() :
    Component("PlayerControlComponent")
{

}

PlayerControlComponent::~PlayerControlComponent()
{

}

void PlayerControlComponent::addSelfToSystems(GameWorld *gw)
{
    gw->getSystem("TickSystem")->addComponent(this);
}

void PlayerControlComponent::removeSelfFromSystems(GameWorld *gw) {
    gw->getSystem("TickSystem")->addComponent(this);
}
