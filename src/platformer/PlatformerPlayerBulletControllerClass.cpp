#include "PlatformerPlayerBulletControllerClass.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"

PlatformerPlayerBulletControllerClass::PlatformerPlayerBulletControllerClass(glm::vec3 dir, float speed) :
      m_speed(speed), m_dir(dir)
{

}

PlatformerPlayerBulletControllerClass::~PlatformerPlayerBulletControllerClass()
{

}

void PlatformerPlayerBulletControllerClass::tick(float seconds) {
    m_gameobject->getComponent<TransformComponent>()->translate(m_dir * seconds * m_speed);
    if (glm::length(m_gameobject->getComponent<TransformComponent>()->getPos()) > DESTROY_BULLET_DISTANCE) {
        m_gameobject->getGameWorld()->markGameObjectForDeletion(m_gameobject->getID());
    }
}
