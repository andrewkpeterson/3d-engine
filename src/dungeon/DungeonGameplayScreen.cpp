#include "DungeonGameplayScreen.h"
#include "src/engine/common/map/MapGenerator.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/warmup/PlayerControlComponent.h"
#include "src/engine/common/component/CylinderCollisionComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/ui/UI.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/warmup/NPCChaseComponent.h"

DungeonGameplayScreen::DungeonGameplayScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonGameplayScreen::~DungeonGameplayScreen()
{

}

void DungeonGameplayScreen::initializeGameWorld() {
    std::shared_ptr<MapSegment> map_seg1 = MapGenerator::createMap(506);
    std::shared_ptr<MapSegment> map_seg2 = MapGenerator::createMap(455);
    std::shared_ptr<MapSegment> map_seg3 = MapGenerator::createMap(800);

    // create player
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<PlayerControlComponent>(std::make_shared<PlayerControlComponent>());
    player->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(1.0f, 2.0f));
    player->addComponent<TransformComponent>(std::make_shared<TransformComponent>(glm::vec3(0,0,0), 2.0));
    Material player_mat;
    player_mat.color = glm::vec3(.4,.3,.8);
    player->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>("cylinder", "playerMat", player_mat));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());

    // create environment
    std::shared_ptr<GameObject> environment = std::make_shared<GameObject>("environment");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<PlayerControlComponent>(std::make_shared<PlayerControlComponent>());
    player->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(1.0f, 2.0f));
    player->addComponent<TransformComponent>(std::make_shared<TransformComponent>(glm::vec3(0,0,0), 2.0));
    player_mat.color = glm::vec3(.4,.3,.8);
    player->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>("cylinder", "playerMat", player_mat));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());
}
