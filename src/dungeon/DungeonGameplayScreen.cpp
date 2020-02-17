#include "DungeonGameplayScreen.h"
#include "src/engine/common/map/MapGenerator.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/ChunkDrawableComponent.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/dungeon/DungeonEnvironmentComponent.h"
#include "src/engine/common/component/CylinderCollisionComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/ui/UI.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/dungeon/DungeonPlayerControlComponent.h"

DungeonGameplayScreen::DungeonGameplayScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonGameplayScreen::~DungeonGameplayScreen()
{

}

void DungeonGameplayScreen::initializeGameWorld() {
    MapGenerator::restartGenerator();
    std::shared_ptr<MapSegment> map_seg1 = MapGenerator::createMap(455);
    std::shared_ptr<MapSegment> map_seg2 = MapGenerator::createMap(455);
    std::shared_ptr<MapSegment> map_seg3 = MapGenerator::createMap(800);

    // create player
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<DungeonPlayerControlComponent>(std::make_shared<DungeonPlayerControlComponent>());
    player->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(1.0f, 2.0f));
    player->addComponent<TransformComponent>(std::make_shared<TransformComponent>(glm::vec3(30,0,20), 2.0));
    Material player_mat;
    player_mat.color = glm::vec3(.4,.3,.8);
    player->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("cylinder", "playerMat", player_mat));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());

    // create environment
    std::shared_ptr<GameObject> environment = std::make_shared<GameObject>("environment");
    environment->addComponent<TransformComponent>(std::make_shared<TransformComponent>(glm::vec3(0,0,0), 1.0));
    environment->addComponent<DungeonEnvironmentComponent>(std::make_shared<DungeonEnvironmentComponent>(7.0, ":/images/terrain.png"));
    m_gameworld->addGameObject(environment);
    // we must add the environment to the gameworld before the environment adds chunks to the gameworld
    environment->getComponent<DungeonEnvironmentComponent>()->makeDungeonChunksFromMapSegment(map_seg1);
    environment->getComponent<DungeonEnvironmentComponent>()->makeDungeonChunksFromMapSegment(map_seg2);
    environment->getComponent<DungeonEnvironmentComponent>()->makeDungeonChunksFromMapSegment(map_seg3);
}
