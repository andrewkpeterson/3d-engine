#include "DungeonStartScreen.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/engine/common/component/UIComponent.h"
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

    std::shared_ptr<Shape> sword_shape = std::make_shared<Shape>("sword");
    ResourceLoader::readObj(":/meshes/sword.obj", sword_shape);
    Material sword_mat;
    sword_mat.textureName = "sword_texture";
    g->addMaterial("sword_mat", sword_mat);
    g->addShape("sword", sword_shape);
    g->addTexture("sword_texture", ":/images/sword.png", Texture::FILTER_METHOD::LINEAR);

    glm::vec2 screen_size = m_app->getScreenSize();
    g->addFont("press_start_2p", ":/fonts/PressStart2P-Regular.ttf");
    std::shared_ptr<GameObject> hud = std::make_shared<GameObject>("HUD");
    hud->addComponent<UIComponent>(std::make_shared<UIComponent>());
    std::shared_ptr<UILabel> x_label = std::make_shared<UILabel>("CREEPER DUNGEON", 20.0f, glm::vec3(1,1,1),
                                                                 glm::vec2(1,1), "white", "press_start_2p");
    hud->getComponent<UIComponent>()->addElement("title",x_label);
    m_gameworld->addGameObject(hud);

    std::shared_ptr<UIControllerComponent> ui_controller = std::make_shared<UIControllerComponent>
                                                           ("sword","sword_mat",glm::vec3(10,10,1.0));
    m_gameworld->getSystem<UISystem>()->setController(ui_controller);



    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<DungeonPauseControlComponent>(std::make_shared<DungeonPauseControlComponent>());
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());


}
