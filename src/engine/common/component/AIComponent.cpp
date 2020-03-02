#include "AIComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/system/TickSystem.h"

AIComponent::AIComponent()
{

}

AIComponent::~AIComponent()
{

}

void AIComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
}

void AIComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
}

void AIComponent::tick(float seconds) {
    bt_root->update(seconds);
}
