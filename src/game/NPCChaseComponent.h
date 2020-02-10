#ifndef NPCCHASECOMPONENT_H
#define NPCCHASECOMPONENT_H

#include "src/engine/common/component/TickComponent.h"

class NPCChaseComponent : public TickComponent
{
public:
    NPCChaseComponent(GameObject *gameobject);
    ~NPCChaseComponent() override;

    void addComponentToSystems() override;
    void removeComponentFromSystems() override;

    void tick(float seconds) override;
};

#endif // NPCCHASECOMPONENT_H
