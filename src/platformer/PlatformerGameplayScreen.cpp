#include "PlatformerGameplayScreen.h"
#include "src/engine/common/map/MapGenerator.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/ChunkDrawableComponent.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/CylinderCollisionComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/ui/UI.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/engine/common/ui/UIShape.h"
#include "src/engine/common/component/DynamicAABCollisionComponent.h"
#include "src/engine/common/system/ChunkStreamingSystem.h"
#include "src/engine/graphics/ResourceLoader.h"
#include "src/engine/common/component/OrthographicUITextComponent.h"
#include "src/engine/common/component/UIComponent.h"
#include "src/engine/common/component/EnvironmentComponent.h"
#include "src/engine/common/system/EnvironmentSystem.h"
#include "src/platformer/PlatformerPlayerControlComponent.h"
#include "src/engine/common/component/EllipsoidComponent.h"
#include "src/engine/common/animation/AnimatedModelComponent.h"
#include "src/engine/common/component/SoundComponent.h"
#include "src/engine/common/animation/AnimatedModel.h"
#include "src/engine/common/animation/AnimationLoader.h"
#include "src/platformer/PlatformerEnemyControllerComponent.h"

PlatformerGameplayScreen::PlatformerGameplayScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

PlatformerGameplayScreen::~PlatformerGameplayScreen()
{

}

void PlatformerGameplayScreen::initializeGameWorld() {

    Graphics *g = Graphics::getGlobalInstance();

    // load in animated model
    std::shared_ptr<AnimatedModel> m = AnimationLoader::loadAnimatedModel("res/meshes/test2.dae");
    std::shared_ptr<GameObject> animation = std::make_shared<GameObject>("animation");
    animation->addComponent<AnimatedModelComponent>(std::make_shared<AnimatedModelComponent>(m));
    animation->addComponent<SoundComponent>(std::make_shared<SoundComponent>());
    //animation->getComponent<SoundComponent>()->addSound(":/sounds/menu-theme.wav");
    //animation->getComponent<SoundComponent>()->playSound(":/sounds/menu-theme.wav");
    animation->getComponent<TransformComponent>()->setPos(glm::vec3(0,10,0));
    animation->getComponent<TransformComponent>()->setScale(1);
    m_gameworld->addGameObject(animation);

    // create environment
    std::shared_ptr<GameObject> environment = std::make_shared<GameObject>("environment");
    environment->addComponent<EnvironmentComponent>(std::make_shared<EnvironmentComponent>(":/meshes/level_island.obj", "env_mat",
                                                                                           ":images/level_island.png",
                                                                                           ":/meshes/level_island.obj"));
    m_gameworld->getSystem<EnvironmentSystem>()->setEnvironment(environment->getComponent<EnvironmentComponent>());
    m_gameworld->addGameObject(environment);

    // create player
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<PlatformerPlayerControlComponent>(std::make_shared<PlatformerPlayerControlComponent>());
    player->addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, .5));
    player->addComponent<EllipsoidComponent>(std::make_shared<EllipsoidComponent>(glm::vec3(.5,.5,.5)));
    player->getComponent<TransformComponent>()->setPos(glm::vec3(0,5,0));
    Material player_mat;
    player_mat.color = glm::vec3(.4,.3,.8);
    player->addComponent<PrimitiveDrawableComponent>
            (std::make_shared<PrimitiveDrawableComponent>("cube", "player_mat", player_mat));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());

    // create test enemy
    std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>("enemy");
    enemy->addComponent<PlatformerEnemyControllerComponent>(std::make_shared<PlatformerEnemyControllerComponent>());
    enemy->addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, 10.0));
    Material enemy_mat;
    player_mat.color = glm::vec3(.4,.3,.8);
    enemy->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "enemymat", enemy_mat));
    enemy->getComponent<TransformComponent>()->setPos(glm::vec3(10,20,10));
    enemy->getComponent<TransformComponent>()->setScale(10.0);
    m_gameworld->addGameObject(enemy);

}
