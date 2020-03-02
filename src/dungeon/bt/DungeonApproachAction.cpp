#include "DungeonApproachAction.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/component/TransformComponent.h"

DungeonApproachAction::DungeonApproachAction(Component *component, std::shared_ptr<MapSegment> segment) :
    Action(component),
    m_seg(segment),
    m_astar(std::make_shared<AStar>(segment))
{

}

DungeonApproachAction::~DungeonApproachAction()
{

}

void DungeonApproachAction::reset() {

}

Status DungeonApproachAction::update(float seconds) {
    glm::vec3 player_pos = m_component->getGameObject()->getGameWorld()->
                           getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
    glm::vec3 enemy_pos = m_component->getGameObject()->getComponent<TransformComponent>()->getPos();


}
