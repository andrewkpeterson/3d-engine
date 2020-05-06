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
#include "src/platformer/prefabs/Enemy.h"
#include "src/platformer/prefabs/Player.h"
#include "src/platformer/PlatformerEnemySpawnerComponent.h"


PlatformerGameplayScreen::PlatformerGameplayScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

PlatformerGameplayScreen::~PlatformerGameplayScreen()
{

}

void PlatformerGameplayScreen::initializeGameWorld() {

    // seed random number generator
    srand(time(nullptr));

    Graphics *g = Graphics::getGlobalInstance();

    // set up font
    g->addFont("press_start_2p", ":/fonts/PressStart2P-Regular.ttf");

    // set up UI
    Material health_bar_mat;
    health_bar_mat.color = glm::vec3(0,1,0);
    g->addMaterial("health_bar_mat", health_bar_mat);

    std::shared_ptr<GameObject> hud = std::make_shared<GameObject>("HUD");
    hud->addComponent<UIComponent>(std::make_shared<UIComponent>());
    std::shared_ptr<UILabel> health_label = std::make_shared<UILabel>(hud->getComponent<UIComponent>().get(),
                                                                      "HEALTH", 20.0f, glm::vec3(1,1,1),
                                                                      glm::vec2(20.0f,60.0f), "white", "press_start_2p");
    hud->getComponent<UIComponent>()->addElement("HEALTH", health_label);
    std::shared_ptr<UIShape> health_bar1 = std::make_shared<UIShape>(hud->getComponent<UIComponent>().get(), "uiquad",
                                                                    glm::vec2(10.0f,10.0f),
                                                                    glm::vec2(40,40),"health_bar_mat");
    hud->getComponent<UIComponent>()->addElement("health_bar1", health_bar1);
    std::shared_ptr<UIShape> health_bar2 = std::make_shared<UIShape>(hud->getComponent<UIComponent>().get(), "uiquad",
                                                                    glm::vec2(60.0f,10.0f),
                                                                    glm::vec2(40,40),"health_bar_mat");
    hud->getComponent<UIComponent>()->addElement("health_bar2", health_bar2);
    std::shared_ptr<UIShape> health_bar3 = std::make_shared<UIShape>(hud->getComponent<UIComponent>().get(), "uiquad",
                                                                    glm::vec2(110.0f,10.0f),
                                                                    glm::vec2(40,40),"health_bar_mat");
    hud->getComponent<UIComponent>()->addElement("health_bar3", health_bar3);
    std::shared_ptr<UILabel> score_label = std::make_shared<UILabel>(hud->getComponent<UIComponent>().get(),
                                                                      "SCORE:", 20.0f, glm::vec3(1,1,1),
                                                                      glm::vec2(20.0f,120.0f), "white", "press_start_2p");
    hud->getComponent<UIComponent>()->addElement("score_label", score_label);
    std::shared_ptr<UILabel> score = std::make_shared<UILabel>(hud->getComponent<UIComponent>().get(),
                                                                      "0", 20.0f, glm::vec3(1,1,1),
                                                                      glm::vec2(150.0f,120.0f), "white", "press_start_2p");
    hud->getComponent<UIComponent>()->addElement("score", score);

    m_gameworld->addGameObject(hud);

    // make the ui
    std::shared_ptr<GameObject> game_over = std::make_shared<GameObject>("game_over");
    game_over->addComponent<UIComponent>(std::make_shared<UIComponent>());
    std::shared_ptr<UILabel> title = std::make_shared<UILabel>(hud->getComponent<UIComponent>().get(),
                                                               "GAME OVER", 100.0f, glm::vec3(1,1,1),
                                                               glm::vec2(1300,1000), "white", "press_start_2p");
    game_over->getComponent<UIComponent>()->addElement("title",title);
    game_over->getComponent<UIComponent>()->getElement("title")->setDraw(false);
    std::shared_ptr<UILabel> directions = std::make_shared<UILabel>(hud->getComponent<UIComponent>().get(),
                                                                    "PRESS SPACEBAR TO RESTART", 50.0f, glm::vec3(1,1,1),
                                                                    glm::vec2(1200,500), "white", "press_start_2p");
    game_over->getComponent<UIComponent>()->addElement("directions",directions);
    game_over->getComponent<UIComponent>()->getElement("directions")->setDraw(false);
    m_gameworld->addGameObject(game_over);

    // load in skybox
    g->setUpSkybox(":/images/bkg1_right.png", ":/images/bkg1_left.png", ":/images/bkg1_top.png",
                   ":/images/bkg1_bot.png", ":/images/bkg1_front.png", ":/images/bkg1_back.png");

    // load in animated model
    std::shared_ptr<AnimatedModel> m = AnimationLoader::loadAnimatedModel("res/meshes/character.dae");
    std::shared_ptr<GameObject> animation = std::make_shared<GameObject>("animation");
    animation->addComponent<SoundComponent>(std::make_shared<SoundComponent>());
    animation->getComponent<SoundComponent>()->addMusic(":/sounds/gameplay.wav");
    animation->getComponent<SoundComponent>()->playMusic(":/sounds/gameplay.wav");

    // create environment
    std::shared_ptr<GameObject> environment = std::make_shared<GameObject>("environment");
    environment->addComponent<EnvironmentComponent>(std::make_shared<EnvironmentComponent>(":/meshes/level_island.obj", "env_mat",
                                                                                           ":images/level_island.png",
                                                                                           ":/meshes/level_island.obj"));
    m_gameworld->getSystem<EnvironmentSystem>()->setEnvironment(environment->getComponent<EnvironmentComponent>());
    m_gameworld->addGameObject(environment);

    // create player
    std::shared_ptr<Player> player = std::make_shared<Player>();
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());


    std::shared_ptr<GameObject> enemy_spawner = std::make_shared<GameObject>("enemy_spawner");
    enemy_spawner->addComponent<PlatformerEnemySpawnerComponent>(std::make_shared<PlatformerEnemySpawnerComponent>());
    m_gameworld->addGameObject(enemy_spawner);
}
