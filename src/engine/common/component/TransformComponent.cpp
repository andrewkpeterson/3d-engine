#include "TransformComponent.h"

TransformComponent::TransformComponent() :
    Component("TransformComponent")
{

}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::addSelfToSystems(std::shared_ptr<GameWorld> gw)
{
    //gw->getSystem("TickSystem")->addComponent(this);
}

void TransformComponent::removeSelfFromSystems(std::shared_ptr<GameWorld> gw) {
    //gw->getSystem("TickSystem")->addComponent(this);
}
