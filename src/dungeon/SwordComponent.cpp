#include "SwordComponent.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/component/DynamicAABCollisionComponent.h"
#include "src/dungeon/DungeonEnemyAIComponent.h"

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

void SwordComponent::addComponentToSystemsAndConnectComponents() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getComponent<DynamicAABCollisionComponent>()->
            setCollisionCallback(std::bind(&SwordComponent::handleCollisionResolutionAndResponse,
                                           this, std::placeholders::_1));
    m_gameobject->getComponent<DynamicAABCollisionComponent>()->setActive(false);
}

void SwordComponent::handleCollisionResolutionAndResponse(Collision collision) {
    std::shared_ptr<DynamicAABCollisionComponent> comp = m_gameobject->getComponent<DynamicAABCollisionComponent>();
    std::string id = collision.collider->getGameObject()->getID();
    if (id.find("enemy") != std::string::npos) {
        collision.collider->getGameObject()->getComponent<DungeonEnemyAIComponent>()->getAttacked();
    }
}

void SwordComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
}

void SwordComponent::tick(float seconds) {
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    t->setObjectPos(glm::vec3(10,0,-10));
    t->setObjectPivotPoint(glm::vec3(0,0,-30));
    t->setObjectRoll(4 * M_PI / 5.0);
    if (swinging) {
        if (t->getObjectYaw() < M_PI / 2.0 && forward) {
            t->setObjectYaw(t->getObjectYaw() + .07);
            t->setObjectPitch(t->getObjectPitch() + .07);
        } else {
            m_gameobject->getComponent<DynamicAABCollisionComponent>()->setActive(true);
            t->setObjectYaw(t->getObjectYaw() - .2);
            t->setObjectPitch(t->getObjectPitch() - .2);
            forward = false;
        }

        if (t->getObjectYaw() < 0) {
            m_gameobject->getComponent<DynamicAABCollisionComponent>()->setActive(false);
            swinging = false;
            t->setObjectYaw(0);
            t->setObjectPitch(0);
        }
    }
    t->setPos(m_gameobject->getGameWorld()->getGameObjectByID("player")->
              getComponent<TransformComponent>()->getPos());
    t->setYaw(m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getYaw() + M_PI);
}
