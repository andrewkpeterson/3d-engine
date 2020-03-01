#ifndef DUNGEONENEMYAICOMPONENT_H
#define DUNGEONENEMYAICOMPONENT_H

#include "src/engine/common/ai/BTNode.h"
#include <memory>

class DungeonEnemyAIComponent
{
public:
    DungeonEnemyAIComponent();
    ~DungeonEnemyAIComponent();

private:
    std::shared_ptr<BTNode> bt_root;
};

#endif // DUNGEONENEMYAICOMPONENT_H
