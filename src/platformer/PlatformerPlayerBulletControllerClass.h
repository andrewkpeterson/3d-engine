#ifndef BULLETCONTROLLERCLASS_H
#define BULLETCONTROLLERCLASS_H

#include "src/engine/common/component/TickComponent.h"

class PlatformerPlayerBulletControllerClass : public TickComponent
{
public:
    PlatformerPlayerBulletControllerClass(glm::vec3 dir, float speed);
    ~PlatformerPlayerBulletControllerClass();
    void tick(float seconds);

private:
    float DESTROY_BULLET_DISTANCE = 100;

    float m_speed;
    glm::vec3 m_dir;
};

#endif // BULLETCONTROLLERCLASS_H
