#include "DrawableComponent.h"
#include "TransformComponent.h"
#include "src/engine/common/system/DrawSystem.h"

DrawableComponent::DrawableComponent() :
    Component(),
    shouldDraw(true)
{
    g = Graphics::getGlobalInstance();
}

DrawableComponent::~DrawableComponent()
{

}

void DrawableComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<DrawSystem>()->addComponent(this);
}

void DrawableComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<DrawSystem>()->removeComponent(this);
}

void DrawableComponent::setDraw(bool draw) {
    shouldDraw = draw;
}
