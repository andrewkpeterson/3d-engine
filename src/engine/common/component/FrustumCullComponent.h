#ifndef FRUSTUMCULLCOMPONENT_H
#define FRUSTUMCULLCOMPONENT_H

#include "DrawableComponent.h"

class FrustumCullComponent : public DrawableComponent
{
public:
    FrustumCullComponent();
    ~FrustumCullComponent();

    void drawSelf() override;
};

#endif // FRUSTUMCULLCOMPONENT_H
