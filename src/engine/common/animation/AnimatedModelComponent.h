#ifndef ANIMATEDMODELCOMPONENT_H
#define ANIMATEDMODELCOMPONENT_H

#include "Joint.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "AnimatedModel.h"
#include "src/engine/common/system/AnimationSystem.h"
#include "src/engine/common/GameWorld.h"

class AnimatedModelComponent : public DrawableComponent
{
public:
    AnimatedModelComponent(std::shared_ptr<AnimatedModel> m);
    ~AnimatedModelComponent();
    virtual void addComponentToSystemsAndConnectComponents() override;
    virtual void removeComponentFromSystems() override;
    void drawSelf(std::shared_ptr<Camera> camera) override;
    void tick(float seconds);

private:
    std::shared_ptr<AnimatedModel> model;

};

#endif // ANIMATEDMODELCOMPONENT_H
