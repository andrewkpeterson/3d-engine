#ifndef DUNGEONPLAYERNEARCONDITION_H
#define DUNGEONPLAYERNEARCONDITION_H

#include "src/engine/common/ai/Condition.h"

class DungeonPlayerNearCondition : public Condition
{
public:
    DungeonPlayerNearCondition(Component *component);
    ~DungeonPlayerNearCondition();
    Status update(float seconds);
    void reset();

private:
    const float NEAR_THRESH = 5;
};

#endif // DUNGEONPLAYERNEARCONDITION_H
