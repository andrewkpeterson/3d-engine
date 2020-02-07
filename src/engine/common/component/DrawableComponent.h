#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent();
    ~DrawableComponent() override;
    void addSelfToSystems(std::shared_ptr<GameWorld> gw) override;
    void removeSelfFromSystems(std::shared_ptr<GameWorld> gw) override;
};

#endif // DRAWABLECOMPONENT_H
