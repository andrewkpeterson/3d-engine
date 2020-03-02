#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "TickComponent.h"
#include "src/engine/common/ai/BTNode.h"

class AIComponent : public TickComponent
{
public:
    AIComponent();
    virtual ~AIComponent() override;
    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;
    void tick(float seconds) override;
    virtual void setUpBehaviorTree() = 0;

protected:
    std::shared_ptr<BTNode> bt_root;
};

#endif // AICOMPONENT_H
