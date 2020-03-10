#include "DungeonPauseScreen.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/engine/common/component/UIComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/component/CameraComponent.h"
#include "DungeonPlayerControlComponent.h"
#include "DungeonPauseControlComponent.h"

DungeonPauseScreen::DungeonPauseScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonPauseScreen::~DungeonPauseScreen()
{

}

void DungeonPauseScreen::initializeGameWorld() {
    Graphics *g = Graphics::getGlobalInstance();

    g->addFont("press_start_2p", ":/fonts/PressStart2P-Regular.ttf");
    std::shared_ptr<GameObject> hud = std::make_shared<GameObject>("HUD");
    hud->addComponent<UIComponent>(std::make_shared<UIComponent>());
    std::shared_ptr<UILabel> x_label = std::make_shared<UILabel>(hud->getComponent<UIComponent>().get(),
                                                                 "PAUSED", 20.0f, glm::vec3(1,1,1),
                                                                 glm::vec2(20.0f,40.0f), "white", "press_start_2p");
    hud->getComponent<UIComponent>()->addElement("pause_label",x_label);
    m_gameworld->addGameObject(hud);

    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<DungeonPauseControlComponent>(std::make_shared<DungeonPauseControlComponent>());
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());

}
