#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "src/engine/common/GameObject.h"
#include "src/platformer/PlatformerEnemyControllerComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/SphereCollisionComponent.h"
#include "src/engine/common/component/EllipsoidComponent.h"
#include "src/engine/common/component/CollisionComponent.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/platformer/PlatformerPlayerBulletControllerComponent.h"
#include "src/engine/graphics/Graphics.h"

class PlayerBullet : public GameObject
{
public:
    PlayerBullet(glm::vec3 pos, glm::vec3 dir) :
          GameObject()
    {
        Material mat;
        mat.color = glm::vec3(1.0,1.0,0);
        addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "player_bulletmat", mat));
        addComponent<PlatformerPlayerBulletControllerComponent>(std::make_shared<PlatformerPlayerBulletControllerComponent>(dir, 50));
        addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, .05, 1));
        addComponent<EllipsoidComponent>(std::make_shared<EllipsoidComponent>(glm::vec3(.01,.01,.01)));
        getComponent<TransformComponent>()->setPos(pos);
        getComponent<TransformComponent>()->setScale(0.1f);
    }

    ~PlayerBullet() {};
};

#endif // PLAYERBULLET_H
