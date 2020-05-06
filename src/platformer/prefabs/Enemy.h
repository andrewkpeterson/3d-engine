#ifndef ENEMY_H
#define ENEMY_H

#include "src/engine/common/GameObject.h"
#include "src/platformer/PlatformerEnemyControllerComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/SphereCollisionComponent.h"
#include "src/engine/common/component/EllipsoidComponent.h"
#include "src/engine/graphics/Graphics.h"

class Enemy : public GameObject
{
public:
    Enemy(glm::vec3 position) : GameObject() {
        addComponent<PlatformerEnemyControllerComponent>(std::make_shared<PlatformerEnemyControllerComponent>());
        addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, 5.0, 0));
        Material enemy_mat;
        enemy_mat.color = glm::vec3(.4,.3,.8);
        addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "enemymat", enemy_mat));
        getComponent<TransformComponent>()->setPos(position);
        getComponent<TransformComponent>()->setScale(10.0);
    }

    ~Enemy() {};
};

#endif // ENEMY_H
