#ifndef DUNGEONATTACKACTION_H
#define DUNGEONATTACKACTION_H

#include "src/engine/common/ai/Action.h"

class DungeonAttackAction : public Action
{
public:
    DungeonAttackAction(Component *component);
    ~DungeonAttackAction() override;
    Status update(float seconds) override;
    void reset() override;
};

#endif // DUNGEONATTACKACTION_H
