#include "PlatformerEnemyBulletControllerComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/EllipsoidComponent.h"
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
