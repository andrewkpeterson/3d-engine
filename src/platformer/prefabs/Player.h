#ifndef PLAYER_H
#define PLAYER_H

#include "src/engine/common/GameObject.h"
#include "src/platformer/PlatformerEnemyControllerComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/SphereCollisionComponent.h"
#include "src/engine/common/component/EllipsoidComponent.h"
#include "src/engine/common/component/CollisionComponent.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/SoundComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/platformer/PlatformerPlayerControlComponent.h"
#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/animation/AnimatedModelComponent.h"
#include "src/engine/common/animation/AnimationLoader.h"

class Player : public GameObject
{
public:
    Player() :
          GameObject("player") {
        addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
        addComponent<PlatformerPlayerControlComponent>(std::make_shared<PlatformerPlayerControlComponent>());
        addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, .05, 1));
        addComponent<EllipsoidComponent>(std::make_shared<EllipsoidComponent>(glm::vec3(.5,.5,.5)));
        getComponent<TransformComponent>()->setPos(glm::vec3(0,10,0));
        getComponent<TransformComponent>()->setObjectPitch(3*M_PI /2);
        getComponent<TransformComponent>()->setScale(.15);
        getComponent<TransformComponent>()->setObjectPos(glm::vec3(0,4.5,0));
        addComponent<SoundComponent>(std::make_shared<SoundComponent>());
        getComponent<SoundComponent>()->addSound(":/sounds/laser.wav");
        Material player_mat;
        player_mat.color = glm::vec3(.4,.3,.8);
        //addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere","playermat", player_mat));
        std::shared_ptr<AnimatedModel> m = AnimationLoader::loadAnimatedModel("res/meshes/character.dae");
        std::shared_ptr<GameObject> animation = std::make_shared<GameObject>("animation");
        addComponent<AnimatedModelComponent>(std::make_shared<AnimatedModelComponent>(m));
    }

    ~Player() {};
};

#endif // PLAYER_H
