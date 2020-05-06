#ifndef BULLETCONTROLLERCLASS_H
#define BULLETCONTROLLERCLASS_H

#include "src/engine/common/component/TickComponent.h"

class PlatformerPlayerBulletControllerComponent : public TickComponent
{
public:
    PlatformerPlayerBulletControllerComponent(glm::vec3 dir, float speed);
    ~PlatformerPlayerBulletControllerComponent();
    void tick(float seconds);

private:
    float DESTROY_BULLET_DISTANCE = 100;

    float m_speed;
    glm::vec3 m_dir;
};

#endif // BULLETCONTROLLERCLASS_H
