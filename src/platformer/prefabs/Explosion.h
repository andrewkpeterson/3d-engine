#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "src/engine/common/GameObject.h"
#include "src/platformer/PlatformerEnemyBulletControllerComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/SphereCollisionComponent.h"
#include "src/platformer/PlatformerExplosionComponent.h"

class Explosion : public GameObject
{
public:
    Explosion(glm::vec3 pos, float total_time, float scale, float size_change) : GameObject() {
        Material mat;
        mat.color = glm::vec3(1.0,1.0,0);
        addComponent<PlatformerExplosionComponent>(std::make_shared<PlatformerExplosionComponent>(total_time, size_change));
        addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "explosion_mat", mat));
        getComponent<TransformComponent>()->setPos(pos);
        getComponent<TransformComponent>()->setScale(scale);
    }

    ~Explosion() {};

};


#endif // EXPLOSION_H
