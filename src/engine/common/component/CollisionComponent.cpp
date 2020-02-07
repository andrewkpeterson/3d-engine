#include "CollisionComponent.h"
#include "src/engine/common/system/CollisionSystem.h"

CollisionComponent::CollisionComponent() :
    Component("CollisionComponent")
{

}

CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::addSelfToSystems(std::shared_ptr<GameWorld> gw) {
    //gw->getSystem("CollisionSystem")->addComponent(this);
    gw->getSystem<CollisionSystem>()->addComponent(getSharedPtr());
}

void CollisionComponent::removeSelfFromSystems(std::shared_ptr<GameWorld> gw) {
    //gw->getSystem("CollisionSystem")->removeComponent(this);
    gw->getSystem<CollisionSystem>()->removeComponent(getSharedPtr());
}
