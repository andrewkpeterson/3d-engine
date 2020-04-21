#include "AnimationSystem.h"
#include "src/engine/common/animation/AnimatedModelComponent.h"

AnimationSystem::AnimationSystem(GameWorld *gameworld) :
      System(gameworld)
{
    g = Graphics::getGlobalInstance();
}

AnimationSystem::~AnimationSystem()
{

}


void AnimationSystem::addComponent(AnimatedModelComponent *component) {
    m_components.insert(component);
}

void AnimationSystem::removeComponent(AnimatedModelComponent *component) {
    m_components.erase(component);
}

void AnimationSystem::draw(Graphics *g) {
    std::shared_ptr<Camera> cam = m_gameworld->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera();
    g->setCamera(cam);
    auto it = m_components.begin();
    while(it != m_components.end()) {
        AnimatedModelComponent *comp = *it;
        comp->drawSelf(cam);
        it++;
    }
}

void AnimationSystem::tick(float seconds) {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        AnimatedModelComponent *comp = *it;
        comp->tick(seconds);
    }
}
