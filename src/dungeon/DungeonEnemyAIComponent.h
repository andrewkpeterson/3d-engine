#ifndef DUNGEONENEMYAICOMPONENT_H
#define DUNGEONENEMYAICOMPONENT_H

#include "src/engine/common/ai/BTNode.h"
#include <memory>
#include "src/engine/common/component/AIComponent.h"
#include "src/engine/common/ai/Selector.h"
#include "src/engine/common/ai/Sequence.h"
#include "src/engine/common/map/MapGenerator.h"

class DungeonEnemyAIComponent : public AIComponent
{
public:
    DungeonEnemyAIComponent(std::shared_ptr<MapSegment> seg);
    ~DungeonEnemyAIComponent() override;
    void setUpBehaviorTree() override;

private:
    std::shared_ptr<MapSegment> m_seg;
};

#endif // DUNGEONENEMYAICOMPONENT_H
