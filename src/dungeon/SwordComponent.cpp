#include "SwordComponent.h"
#include "src/engine/common/GameWorld.h"

SwordComponent::SwordComponent()
{

}

SwordComponent::~SwordComponent()
{

}

void SwordComponent::swing() {

}

void SwordComponent::tick(float seconds) {
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    t->setObjectPos(glm::vec3(10,0,-20));
    t->setPos(m_gameobject->getGameWorld()->getGameObjectByID("player")->
              getComponent<TransformComponent>()->getPos());
    t->setYaw(m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getYaw() + M_PI);
}
