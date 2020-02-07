#include "TransformComponent.h"

TransformComponent::TransformComponent() :
    Component("TransformComponent")
{

}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::addSelfToSystems(GameWorld *gw)
{
    gw->getSystem("TickSystem")->addComponent(this);
}

void TransformComponent::removeSelfFromSystems(GameWorld *gw) {
    gw->getSystem("TickSystem")->addComponent(this);
}
