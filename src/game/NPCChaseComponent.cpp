#include "NPCChaseComponent.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/component/TransformComponent.h"

NPCChaseComponent::NPCChaseComponent(GameObject *gameobject) :
    TickComponent (gameobject)
{

}

NPCChaseComponent::~NPCChaseComponent()
{

}

void NPCChaseComponent::tick(float seconds) {
    // get the player gameobject and then extract its position.
    // move toward the player
    glm::vec3 player_pos = m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
    glm::vec3 npc_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
    glm::vec3 move_dir = glm::vec3(player_pos.x - npc_pos.x, 0.0f, player_pos.z - npc_pos.z);
    m_gameobject->getComponent<TransformComponent>()->setPos(npc_pos + 1.0f*move_dir*seconds);
}

void NPCChaseComponent::addComponentToSystems()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
}

void NPCChaseComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
}
