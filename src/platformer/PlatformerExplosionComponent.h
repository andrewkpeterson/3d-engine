#ifndef PLATFORMEREXPLOSIONCOMPONENT_H
#define PLATFORMEREXPLOSIONCOMPONENT_H

#include "src/engine/common/component/TickComponent.h"

class PlatformerExplosionComponent : public TickComponent
{
public:
    PlatformerExplosionComponent(float total_time, float size_change);
    ~PlatformerExplosionComponent();

    void tick(float seconds) override;

private:
    float saved_time;
    float m_total_time;
    float m_size_change;
};

#endif // PLATFORMEREXPLOSIONCOMPONENT_H
