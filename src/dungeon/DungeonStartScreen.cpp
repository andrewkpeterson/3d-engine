#include "DungeonStartScreen.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/engine/common/ui/UIButton.h"
#include "src/engine/common/component/UIComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/system/UISystem.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/UIControllerComponent.h"
#include "DungeonPlayerControlComponent.h"
#include "DungeonPauseControlComponent.h"
#include "src/engine/graphics/ResourceLoader.h"
#include "src/engine/graphics/Shape.h"

DungeonStartScreen::DungeonStartScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonStartScreen::~DungeonStartScreen()
{

}

void DungeonStartScreen::initializeGameWorld() {
    Graphics *g = Graphics::getGlobalInstance();

    glm::vec2 screen_size = m_app->getScreenSize();

    g->addFont("press_start_2p", ":/fonts/PressStart2P-Regular.ttf");


    // make the cursor material
    Material cursor_mat;
    cursor_mat.textureName = "cursor_texture";
    g->addMaterial("cursor_mat", cursor_mat);
    g->addTexture("cursor_texture", ":/images/sword_cursor.png", Texture::FILTER_METHOD::NEAREST);

    // make the button background material
    Material button_mat;
    button_mat.color = glm::vec3(0,0,0);
    g->addMaterial("button_mat", button_mat);

    // make the ui
    std::shared_ptr<GameObject> hud = std::make_shared<GameObject>("HUD");
    hud->addComponent<UIComponent>(std::make_shared<UIComponent>());
    std::shared_ptr<UILabel> title = std::make_shared<UILabel>("CREEPER DUNGEON", 20.0f, glm::vec3(1,1,1),
                                                                 glm::vec2(1,1), "white", "press_start_2p");
    hud->getComponent<UIComponent>()->addElement("title",title);
    std::shared_ptr<UIButton> start_button = std::make_shared<UIButton>(glm::vec2(50,1),"Click Here to Start!","press_start_2p",
                                                                        glm::vec3(50,10,0), 50.0f,"white","button_mat",
                                                                        std::bind(&DungeonStartScreen::goToGameplay, this));
    m_gameworld->addGameObject(hud);

    std::shared_ptr<GameObject> ui_controller_object = std::make_shared<GameObject>("controller");
    ui_controller_object->addComponent<UIControllerComponent>(std::make_shared<UIControllerComponent>
                                                              ("uiquad","cursor_mat",glm::vec3(100.0,100.0,10.0)));
    m_gameworld->addGameObject(ui_controller_object);
    m_gameworld->getSystem<UISystem>()->setController(ui_controller_object->getComponent<UIControllerComponent>());

    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<DungeonPauseControlComponent>(std::make_shared<DungeonPauseControlComponent>());
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());


}

void DungeonStartScreen::goToGameplay() {
    m_app->changeScreen("gameplay");
}
