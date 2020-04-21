#include "PlatformerEnemyBulletControllerComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"


PlatformerEnemyBulletControllerComponent::PlatformerEnemyBulletControllerComponent(glm::vec3 dir, float speed, glm::vec3 acceleration,
                                                                                   bool radial, glm::vec3 center) :
      m_speed(speed), m_dir(dir), m_acceleration(acceleration), m_radial(radial), m_center(center)
{

}

PlatformerEnemyBulletControllerComponent::~PlatformerEnemyBulletControllerComponent()
{

}

void PlatformerEnemyBulletControllerComponent::tick(float seconds) {
    if (!m_radial) {
        m_dir += m_acceleration;
        m_dir = glm::normalize(m_dir);
    } else {

    }

    m_gameobject->getComponent<TransformComponent>()->translate(m_dir * seconds * m_speed);
    if (glm::length(m_gameobject->getComponent<TransformComponent>()->getPos()) > DESTROY_BULLET_DISTANCE) {
        m_gameobject->getGameWorld()->markGameObjectForDeletion(m_gameobject->getID());
    }
}
