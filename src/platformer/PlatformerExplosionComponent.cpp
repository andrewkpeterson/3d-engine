#include "PlatformerExplosionComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/component/TransformComponent.h"

PlatformerExplosionComponent::PlatformerExplosionComponent(float total_time, float size_change) :
      saved_time(0), m_total_time(total_time), m_size_change(size_change)
{

}

PlatformerExplosionComponent::~PlatformerExplosionComponent()
{

}

void PlatformerExplosionComponent::tick(float seconds) {
    saved_time += seconds;
    if (saved_time > m_total_time) {
        m_gameobject->getGameWorld()->markGameObjectForDeletion(m_gameobject->getID());
    }
    float curr_size = m_gameobject->getComponent<TransformComponent>()->getScale();
    m_gameobject->getComponent<TransformComponent>()->setScale(curr_size + m_size_change);
}
