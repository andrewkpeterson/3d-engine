#ifndef NPCCHASECOMPONENT_H
#define NPCCHASECOMPONENT_H

#include "src/engine/common/component/TickComponent.h"

class NPCChaseComponent : public TickComponent
{
public:
    NPCChaseComponent();
    ~NPCChaseComponent() override;

    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;

    void tick(float seconds) override;
};

#endif // NPCCHASECOMPONENT_H
