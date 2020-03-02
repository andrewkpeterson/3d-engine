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
    DungeonApproachAction(Component *component, std::shared_ptr<MapSegment> segment, float size);
    ~DungeonApproachAction() override;
    Status update(float seconds) override;
    void reset() override;

private:
    std::shared_ptr<MapSegment> m_seg;
    std::shared_ptr<AStar> m_astar;
    float m_size;
    const float ENEMY_SPEED = .2f;
    glm::vec3 current_direction;
    float m_counter;
    const float UPDATE_TIME = 1.0f;
    std::vector<std::pair<int, int>> curr_path;
    int curr_step;
    const float EPSILON = .1;
};

#endif // DUNGEONAPPROACHACTION_H
