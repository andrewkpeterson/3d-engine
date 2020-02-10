#include "WarmupGameplayScreen.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/PlayerControlComponent.h"
#include "src/engine/common/component/CylinderCollisionComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/ui/UI.h"
#include "src/engine/common/ui/UILabel.h"

WarmupGameplayScreen::WarmupGameplayScreen(Graphics *g, WarmupApplication *parent_app) :
    Screen(parent_app)
{
    initializeGameWorld();
}

WarmupGameplayScreen::~WarmupGameplayScreen() {
}

void WarmupGameplayScreen::initializeGameWorld() {
    //set up UI
    std::shared_ptr<UI> ui = std::make_shared<UI>(m_gameworld.get());
    std::shared_ptr<UILabel> label = std::make_shared<UILabel>("Press mouse to play", 80.0f, glm::vec3(1,1,1), glm::vec2(20.0f,20.0f), "white");
    ui->addElement(label);
    m_gameworld->addUI(ui, "HUD");
    m_gameworld->setActiveUI("HUD");

    //make floor
    std::shared_ptr<GameObject> floor = std::make_shared<GameObject>(m_gameworld.get());
    floor->addComponent<TransformComponent>(std::make_shared<TransformComponent>(floor.get(), glm::vec3(0,0,0), 20.0));
    Material floor_mat;
    floor_mat.textureName = "grass";
    floor_mat.textureRepeat = glm::vec2(10,10);
    floor->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(floor.get(), "quad", "grassTexture", floor_mat));
    m_gameworld->addGameObject(floor);

    //make camera and player representation
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>(m_gameworld.get());
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(player.get(), glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<PlayerControlComponent>(std::make_shared<PlayerControlComponent>(player.get()));
    player->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(player.get(), 1.0f, 2.0f));
    player->addComponent<TransformComponent>(std::make_shared<TransformComponent>(player.get(), glm::vec3(0,0,0), 2.0));
    Material player_mat;
    player_mat.color = glm::vec3(.4,.3,.8);
    player->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(player.get(), "cylinder", "playerMat", player_mat));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());

    //make NPC
    std::shared_ptr<GameObject> npc = std::make_shared<GameObject>(m_gameworld.get());
    npc->addComponent<TransformComponent>(std::make_shared<TransformComponent>(npc.get(), glm::vec3(1,0,1), 2.0));
    npc->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(npc.get(), 1.0f, 2.0f));
    Material npc_mat;
    npc_mat.color = glm::vec3(.8,0,.3);
    npc->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(npc.get(), "cylinder", "npcMat", npc_mat));
    m_gameworld->addGameObject(npc);

}

