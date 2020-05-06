#include "PlatformerPlayerBulletControllerComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/component/EllipsoidComponent.h"

PlatformerPlayerBulletControllerComponent::PlatformerPlayerBulletControllerComponent(glm::vec3 dir, float speed) :
      m_speed(speed), m_dir(dir)
{

}

PlatformerPlayerBulletControllerComponent::~PlatformerPlayerBulletControllerComponent()
{

}

void PlatformerPlayerBulletControllerComponent::tick(float seconds) {

    glm::vec3 pos = m_gameobject->getComponent<TransformComponent>()->getPos();

    std::pair<std::vector<EllipsoidTriangleCollision>, glm::vec3> collisions =  m_gameobject->
        getComponent<EllipsoidComponent>()->checkCollisionAndTranslate(pos, pos + m_dir * seconds * m_speed, false);

    if (collisions.first.size() > 0) {
        m_gameobject->getGameWorld()->markGameObjectForDeletion(m_gameobject->getID());
    }

    if (glm::length(m_gameobject->getComponent<TransformComponent>()->getPos()) > DESTROY_BULLET_DISTANCE) {
        m_gameobject->getGameWorld()->markGameObjectForDeletion(m_gameobject->getID());
    }
}
