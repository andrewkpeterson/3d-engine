#ifndef SWORDCOMPONENT_H
#define SWORDCOMPONENT_H

#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/TickComponent.h"
#include "src/engine/common/system/CollisionSystem.h"
#include "src/engine/common/component/CollisionComponent.h"

class SwordComponent : public TickComponent
{
public:
    SwordComponent();
    ~SwordComponent() override;
    void tick(float seconds) override;
    void swing();
    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;
    void handleCollisionResolutionAndResponse(Collision collision);

private:
    bool swinging;
    bool forward;
};

#endif // SWORDCOMPONENT_H
