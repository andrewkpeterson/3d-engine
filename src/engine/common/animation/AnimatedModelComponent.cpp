#include "AnimatedModelComponent.h"
#include "src/engine/common/component/TransformComponent.h"

AnimatedModelComponent::AnimatedModelComponent(std::shared_ptr<AnimatedModel> m) :
      DrawableComponent(), model(m), saved_time(.1), curr_anim("")
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

void AnimatedModelComponent::setAnimation(std::string anim_name, float transition_time) {
    if (std::strcmp(anim_name.c_str(), curr_anim.c_str()) != 0) {
        //std::cout << anim_name << std::endl;
        model->switchAnimation(anim_name, transition_time);
        curr_anim = anim_name;
    }
}

void AnimatedModelComponent::drawSelf(std::shared_ptr<Camera> camera) {
    if (shouldDraw) {
        std::vector<glm::mat4x4> offsets = model->getCurrentTotalPoseTransformations();
        for (int i = 0; i < offsets.size(); i++) {
            g->clearTransform();
            m_gameobject->getComponent<TransformComponent>()->setObjectToWorldTransform();
            m_gameobject->getComponent<TransformComponent>()->setObjectSpaceOrientation();
            g->translate(glm::vec3(offsets[i] * glm::vec4(0,0,0,1)));
            g->scale(.3);
            //g->drawShape("sphere");
        }

        offsets = model->getOffsetMatrices();
        for (int i = 0; i < offsets.size(); i++) {
            g->clearTransform();
            m_gameobject->getComponent<TransformComponent>()->setObjectToWorldTransform();
            m_gameobject->getComponent<TransformComponent>()->setObjectSpaceOrientation();
            g->translate(glm::vec3(glm::inverse(offsets[i]) * glm::vec4(0,0,0,1)));
            g->scale(.3);
            //g->drawShape("sphere");
        }

        g->clearTransform();
        m_gameobject->getComponent<TransformComponent>()->setObjectToWorldTransform();
        m_gameobject->getComponent<TransformComponent>()->setObjectSpaceOrientation();
        model->draw();
    }
}

void AnimatedModelComponent::queueAnimation(std::string anim_name) {
    model->queueAnimation(anim_name);
}

void AnimatedModelComponent::tick(float seconds) {
    model->tick(seconds);
}
