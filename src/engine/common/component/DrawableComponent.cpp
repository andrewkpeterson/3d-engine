#include "DrawableComponent.h"

DrawableComponent::DrawableComponent() :
    Component("DrawableComponent")
{

}

DrawableComponent::~DrawableComponent()
{

}

void DrawableComponent::addSelfToSystems(GameWorld *gw)
{
    gw->getSystem("DrawSystem")->addComponent(this);
}

void DrawableComponent::removeSelfFromSystems(GameWorld *gw) {
    gw->getSystem("DrawSystem")->removeComponent(this);
}
