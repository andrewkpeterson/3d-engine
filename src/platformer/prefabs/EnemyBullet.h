#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "src/engine/common/GameObject.h"
#include "src/platformer/PlatformerEnemyBulletControllerComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/SphereCollisionComponent.h"
#include "src/engine/common/component/EllipsoidComponent.h"

class EnemyBullet : public GameObject
{
public:
    EnemyBullet(glm::vec3 start_pos, glm::vec3 dir, float speed, float scale) : GameObject() {
        Material mat;
        mat.color = glm::vec3(1.0,0,0);
        addComponent<PlatformerEnemyBulletControllerComponent>(
            std::make_shared<PlatformerEnemyBulletControllerComponent>(dir, speed, glm::vec3(0,0,0), false, glm::vec3(0,0,0)));
        addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, .75, 0));
        addComponent<EllipsoidComponent>(std::make_shared<EllipsoidComponent>(glm::vec3(.4,.4,.4)));
        addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "enemy_bulletmat", mat));
        getComponent<TransformComponent>()->setPos(start_pos);
        getComponent<TransformComponent>()->setScale(scale);
    }

    ~EnemyBullet() {};

};

#endif // ENEMYBULLET_H
