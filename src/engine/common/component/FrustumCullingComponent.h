#ifndef FRUSTUMCULLCOMPONENT_H
#define FRUSTUMCULLCOMPONENT_H

#include "DrawableComponent.h"
#include "ChunkDrawableComponent.h"

class FrustumCullingComponent : public ChunkDrawableComponent
{
public:
    FrustumCullingComponent();
    ~FrustumCullingComponent();

    void drawSelf() override;

};

#endif // FRUSTUMCULLCOMPONENT_H
