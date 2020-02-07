#include "CollisionComponent.h"

CollisionComponent::CollisionComponent() :
    Component("CollisionComponent")
{

}

CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::addSelfToSystems(GameWorld *gw) {
    gw->getSystem("CollisionSystem")->addComponent(this);
}

void CollisionComponent::removeSelfFromSystems(GameWorld *gw) {
    gw->getSystem("CollisionSystem")->removeComponent(this);
}
