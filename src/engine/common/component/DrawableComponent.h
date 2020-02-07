#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent();
    ~DrawableComponent() override;
    void addSelfToSystems(GameWorld *gw) override;
    void removeSelfFromSystems(GameWorld *gw) override;
};

#endif // DRAWABLECOMPONENT_H
