#include "TickComponent.h"

TickComponent::TickComponent(std::shared_ptr<GameObject> gameobject) :
    Component(gameobject)
{

}

TickComponent::~TickComponent()
{

}

void TickComponent::tick(float seconds)
{

}
