#include "DungeonEnemyAIComponent.h"
#include "src/dungeon/bt/DungeonPlayerNearCondition.h"
#include "src/dungeon/bt/DungeonApproachAction.h"
#include "src/dungeon/bt/DungeonAttackAction.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/CollisionSystem.h"
#include "src/engine/common/component/CollisionComponent.h"
#include "src/engine/common/component/DynamicAABCollisionComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"

DungeonEnemyAIComponent::DungeonEnemyAIComponent(std::shared_ptr<MapSegment> seg) :
    AIComponent(),
    m_seg(seg),
    damage_count(0),
    damaged(false)
{
    setUpBehaviorTree();
}

DungeonEnemyAIComponent::~DungeonEnemyAIComponent()
{

}

void DungeonEnemyAIComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getComponent<DynamicAABCollisionComponent>()->
            setCollisionCallback(std::bind(&DungeonEnemyAIComponent::handleCollisionResolutionAndResponse,
                                           this, std::placeholders::_1));
}

void DungeonEnemyAIComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
}

void DungeonEnemyAIComponent::handleCollisionResolutionAndResponse(Collision collision) {
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    if (collision.collider->canMove()) {
        t->translate(collision.half_mtv);
    } else {
        t->translate(2.0f*collision.half_mtv);
    }
}

void DungeonEnemyAIComponent::tick(float seconds) {
    AIComponent::tick(seconds);
    if (damaged) {
        damage_count += seconds;
        if (damage_count > DAMAGE_TIME) {
            damaged = false;
            m_gameobject->getComponent<PrimitiveDrawableComponent>()->setMaterial("enemy_mat");
        }
    }
}

void DungeonEnemyAIComponent::setUpBehaviorTree() {
    std::vector<std::shared_ptr<BTNode>> offense_children;
    offense_children.push_back(std::make_shared<DungeonPlayerNearCondition>(this));
    offense_children.push_back(std::make_shared<DungeonAttackAction>(this));
    std::shared_ptr<Sequence> offense = std::make_shared<Sequence>(this, offense_children);

    std::vector<std::shared_ptr<BTNode>> main_children;
    main_children.push_back(offense);
    main_children.push_back(std::make_shared<DungeonApproachAction>(this, m_seg, 7.0));
    bt_root = std::make_shared<Selector>(this, main_children);
}

void DungeonEnemyAIComponent::getAttacked() {
    m_gameobject->getComponent<PrimitiveDrawableComponent>()->setMaterial("damaged_mat");
    damaged = true;
}
