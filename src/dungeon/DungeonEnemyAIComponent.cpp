#include "DungeonEnemyAIComponent.h"
#include "src/dungeon/bt/DungeonPlayerNearCondition.h"
#include "src/dungeon/bt/DungeonApproachAction.h"
#include "src/dungeon/bt/DungeonAttackAction.h"

DungeonEnemyAIComponent::DungeonEnemyAIComponent(std::shared_ptr<MapSegment> seg) :
    AIComponent(),
    m_seg(seg)

{
    setUpBehaviorTree();
}

DungeonEnemyAIComponent::~DungeonEnemyAIComponent()
{

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
