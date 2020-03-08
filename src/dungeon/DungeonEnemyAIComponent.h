#ifndef DUNGEONENEMYAICOMPONENT_H
#define DUNGEONENEMYAICOMPONENT_H

#include "src/engine/common/ai/BTNode.h"
#include <memory>
#include "src/engine/common/component/AIComponent.h"
#include "src/engine/common/ai/Selector.h"
#include "src/engine/common/ai/Sequence.h"
#include "src/engine/common/map/MapGenerator.h"
#include "src/engine/common/component/CollisionComponent.h"

class DungeonEnemyAIComponent : public AIComponent
{
public:
    DungeonEnemyAIComponent(std::shared_ptr<MapSegment> seg);
    ~DungeonEnemyAIComponent() override;
    void setUpBehaviorTree() override;
    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;
    void handleCollisionResolutionAndResponse(Collision collision);
    void getAttacked();
    void tick(float seconds) override;

private:
    std::shared_ptr<MapSegment> m_seg;
    const float DAMAGE_TIME = .1;
    float damage_count;
    bool damaged;
    float m_health;
};

#endif // DUNGEONENEMYAICOMPONENT_H
