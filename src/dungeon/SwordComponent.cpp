#include "SwordComponent.h"
#include "src/engine/common/GameWorld.h"

SwordComponent::SwordComponent() :
    swinging(false),
    forward(false)
{

}

SwordComponent::~SwordComponent()
{

}

void SwordComponent::swing() {
    if (!swinging) {
        swinging = true;
        forward = true;
    }
}

void SwordComponent::tick(float seconds) {
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    t->setObjectPos(glm::vec3(10,0,-10));
    t->setObjectPivotPoint(glm::vec3(0,0,-30));
    t->setObjectRoll(3 * M_PI / 5.0);
    if (swinging) {
        if (t->getObjectYaw() < M_PI / 2.0 && forward) {
            t->setObjectYaw(t->getObjectYaw() + .07);
            t->setObjectPitch(t->getObjectPitch() + .07);
        } else {
            t->setObjectYaw(t->getObjectYaw() - .2);
            t->setObjectPitch(t->getObjectPitch() - .2);
            forward = false;
        }

        if (t->getObjectYaw() < 0) {
            swinging = false;
            t->setObjectYaw(0);
            t->setObjectPitch(0);
        }
    }
    t->setPos(m_gameobject->getGameWorld()->getGameObjectByID("player")->
              getComponent<TransformComponent>()->getPos());
    t->setYaw(m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getYaw() + M_PI);

}
