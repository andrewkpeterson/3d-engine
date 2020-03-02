#ifndef DUNGEONAPPROACHACTION_H
#define DUNGEONAPPROACHACTION_H

#include "src/engine/common/ai/BTNode.h"
#include "src/engine/common/ai/Action.h"
#include "src/engine/common/map/MapGenerator.h"
#include "src/engine/common/ai/AStar.h"
#include <memory>

class DungeonApproachAction : public Action
{
public:
    DungeonApproachAction(Component *component, std::shared_ptr<MapSegment> segment);
    ~DungeonApproachAction();
    Status update(float seconds) override;
    void reset() override;

private:
    std::shared_ptr<MapSegment> m_seg;
    std::shared_ptr<AStar> m_astar;
};

#endif // DUNGEONAPPROACHACTION_H
