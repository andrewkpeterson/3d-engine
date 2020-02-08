#include "PlayerControlComponent.h"
#include "src/engine/common/system/TickSystem.h"

PlayerControlComponent::PlayerControlComponent(std::shared_ptr<GameObject> gameobject) :
    Component("PlayerControlComponent", gameobject)
{

}

PlayerControlComponent::~PlayerControlComponent()
{

}

void PlayerControlComponent::addGameObjectToSystems()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addGameObject(m_gameobject);
}

void PlayerControlComponent::removeGameObjectFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeGameObject(m_gameobject);
}
