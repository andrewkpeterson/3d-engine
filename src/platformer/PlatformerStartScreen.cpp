#include "PlatformerStartScreen.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/engine/common/ui/UIButton.h"
#include "src/engine/common/component/UIComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/system/UISystem.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/UIControllerComponent.h"
#include "src/engine/graphics/ResourceLoader.h"
#include "src/engine/graphics/Shape.h"
#include "src/engine/common/Application.h"
#include "PlatformerStartScreenController.h"
#include "src/engine/common/animation/AnimatedModelComponent.h"
#include "src/engine/common/animation/AnimationLoader.h"
#include "src/engine/common/component/SoundComponent.h"

PlatformerStartScreen::PlatformerStartScreen(Application *parent) :
      Screen(parent)
{
    initializeGameWorld();
}

PlatformerStartScreen::~PlatformerStartScreen()
{

}

void PlatformerStartScreen::initializeGameWorld() {
    Graphics *g = Graphics::getGlobalInstance();

    glm::vec2 screen_size = m_app->getScreenSize();

    g->addFont("press_start_2p", ":/fonts/PressStart2P-Regular.ttf");

    g->setUpSkybox(":/images/bkg1_right.png", ":/images/bkg1_left.png", ":/images/bkg1_top.png",
                   ":/images/bkg1_bot.png", ":/images/bkg1_front.png", ":/images/bkg1_back.png");

    // make the ui
    std::shared_ptr<GameObject> hud = std::make_shared<GameObject>("HUD");
    hud->addComponent<UIComponent>(std::make_shared<UIComponent>());
    std::shared_ptr<UILabel> title = std::make_shared<UILabel>(hud->getComponent<UIComponent>().get(),
                                                               "SPACE FORCE: STAR DEFENDER", 100.0f, glm::vec3(1,1,1),
                                                               glm::vec2(500,1000), "white", "press_start_2p");
    hud->getComponent<UIComponent>()->addElement("title",title);
    std::shared_ptr<UILabel> directions = std::make_shared<UILabel>(hud->getComponent<UIComponent>().get(),
                                                               "PRESS SPACEBAR TO START", 50.0f, glm::vec3(1,1,1),
                                                               glm::vec2(1200,500), "white", "press_start_2p");
    hud->getComponent<UIComponent>()->addElement("directions",directions);
    m_gameworld->addGameObject(hud);

    std::shared_ptr<GameObject> music_player = std::make_shared<GameObject>("music_player");
    music_player->addComponent<SoundComponent>(std::make_shared<SoundComponent>());
    music_player->getComponent<SoundComponent>()->addMusic(":/sounds/intro.wav");
    music_player->getComponent<SoundComponent>()->playMusic(":/sounds/intro.wav");
    m_gameworld->addGameObject(music_player);

    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());
    m_gameworld->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera()->setYaw(M_PI / 2.0f);
    std::shared_ptr<GameObject> graphics_controller = std::make_shared<GameObject>("graphics_controller");
    graphics_controller->addComponent<PlatformerStartScreenController>(std::make_shared<PlatformerStartScreenController>());
    m_gameworld->addGameObject(graphics_controller);
}

void PlatformerStartScreen::goToGameplay() {
    m_app->changeScreen("gameplay");
}
