#include "DungeonPlayerNearCondition.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/component/TransformComponent.h"

DungeonPlayerNearCondition::DungeonPlayerNearCondition(Component *component) :
    Condition (component)
{

}

DungeonPlayerNearCondition::~DungeonPlayerNearCondition()
{

}

void DungeonPlayerNearCondition::reset() {

}

Status DungeonPlayerNearCondition::update(float seconds) {
    glm::vec3 player_pos = m_component->getGameObject()->getGameWorld()->
                           getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
    glm::vec3 enemy_pos = m_component->getGameObject()->getComponent<TransformComponent>()->getPos();
    if (glm::length(player_pos - enemy_pos) < NEAR_THRESH) {
        return SUCCESS;
    }

    return FAIL;
}
