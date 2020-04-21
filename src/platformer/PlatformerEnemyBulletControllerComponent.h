#ifndef PLATFORMERENEMYBULLETCONTROLLERCOMPONENT_H
#define PLATFORMERENEMYBULLETCONTROLLERCOMPONENT_H

#include "src/engine/common/component/TickComponent.h"

class PlatformerEnemyBulletControllerComponent : public TickComponent
{
public:
    PlatformerEnemyBulletControllerComponent(glm::vec3 dir, float speed, glm::vec3 acceleration, bool radial, glm::vec3 center);
    ~PlatformerEnemyBulletControllerComponent();
    void tick(float seconds);

private:
    float DESTROY_BULLET_DISTANCE = 100;

    float m_speed;
    glm::vec3 m_dir;
    glm::vec3 m_acceleration;
    bool m_radial;
    glm::vec3 m_center;
};

#endif // PLATFORMERENEMYBULLETCONTROLLERCOMPONENT_H
