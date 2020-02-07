#include "DrawableComponent.h"

DrawableComponent::DrawableComponent() :
    Component("DrawableComponent")
{

}

DrawableComponent::~DrawableComponent()
{

}

void DrawableComponent::addSelfToSystems(std::shared_ptr<GameWorld> gw)
{
    //gw->getSystem("DrawSystem")->addComponent(this);
}

void DrawableComponent::removeSelfFromSystems(std::shared_ptr<GameWorld> gw) {
    //gw->getSystem("DrawSystem")->removeComponent(this);
}
