#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "System.h"
#include "src/engine/common/GameWorld.h"
#include "CameraSystem.h"

class AnimatedModelComponent;

class AnimationSystem : public System
{
public:
    AnimationSystem(GameWorld *gameworld);
    ~AnimationSystem();

    void addComponent(AnimatedModelComponent *component);
    void removeComponent(AnimatedModelComponent *component);
    void tick(float seconds);
    void draw(Graphics *g);

private:
    Graphics *g;
    std::unordered_set<AnimatedModelComponent*> m_components;
};

#endif // ANIMATIONSYSTEM_H
