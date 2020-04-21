#include "AnimatedModelComponent.h"
#include "src/engine/common/component/TransformComponent.h"

AnimatedModelComponent::AnimatedModelComponent(std::shared_ptr<AnimatedModel> m) :
      DrawableComponent(), model(m)
{

}

AnimatedModelComponent::~AnimatedModelComponent()
{

}

void AnimatedModelComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<AnimationSystem>()->addComponent(this);
}

void AnimatedModelComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<AnimationSystem>()->removeComponent(this);
}

void AnimatedModelComponent::drawSelf(std::shared_ptr<Camera> camera) {
    g->clearTransform();
    m_gameobject->getComponent<TransformComponent>()->setObjectToWorldTransform();
    m_gameobject->getComponent<TransformComponent>()->setObjectSpaceOrientation();
    model->draw();
}

void AnimatedModelComponent::tick(float seconds) {
    model->tick(seconds);
}
