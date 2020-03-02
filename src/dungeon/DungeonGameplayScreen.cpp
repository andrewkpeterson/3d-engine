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
#include "src/engine/common/component/DynamicAABCollisionComponent.h"
#include "src/engine/common/system/ChunkStreamingSystem.h"
#include "src/dungeon/DungeonEnemyAIComponent.h"

DungeonGameplayScreen::DungeonGameplayScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonGameplayScreen::~DungeonGameplayScreen()
{

}

void DungeonGameplayScreen::initializeGameWorld() {
    std::shared_ptr<UI> ui = std::make_shared<UI>();
    std::shared_ptr<UILabel> x_label = std::make_shared<UILabel>("x", 20.0f, glm::vec3(1,1,1), glm::vec2(20.0f,40.0f), "white");
    ui->addElement("xlabel", x_label);
    ui->setShouldDisplay(true);
    std::shared_ptr<UILabel> z_label = std::make_shared<UILabel>("z", 20.0f, glm::vec3(1,1,1), glm::vec2(20.0f,20.0f), "white");
    ui->addElement("zlabel", z_label);
    ui->setShouldDisplay(true);
    m_gameworld->addUI(ui, "HUD");
    m_gameworld->setActiveUI("HUD");

    // create player
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<DungeonPlayerControlComponent>(std::make_shared<DungeonPlayerControlComponent>());
    //player->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(true, true, 1.0, 2.0));
    player->addComponent<DynamicAABCollisionComponent>(std::make_shared<DynamicAABCollisionComponent>(true, true, glm::vec3(1,1,1)));
    //player->addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(true, true, 2.0));
    player->getComponent<TransformComponent>()->setPos(glm::vec3(31,1,20));
    player->getComponent<TransformComponent>()->setScale(2.0f);
    Material player_mat;
    player_mat.color = glm::vec3(.4,.3,.8);
    player->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("cube", "playerMat", player_mat));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());

    // create sphere npc
    /*
    std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>("sphere_npc");
    sphere->addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, 1.5));
    sphere->getComponent<TransformComponent>()->setPos(glm::vec3(28,1,20));
    sphere->getComponent<TransformComponent>()->setScale(2.0f);
    Material sphere_mat;
    sphere_mat.color = glm::vec3(.4,.8,.3);
    sphere->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "sphere_mat", sphere_mat));
    m_gameworld->addGameObject(sphere);

    // create cylinder npc
    std::shared_ptr<GameObject> cylinder = std::make_shared<GameObject>("cylinder_npc");
    cylinder->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(false, true, 1.5,2.0));
    cylinder->getComponent<TransformComponent>()->setPos(glm::vec3(40,0,20));
    cylinder->getComponent<TransformComponent>()->setScale(2.0f);
    Material cylinder_mat;
    cylinder_mat.color = glm::vec3(.4,.8,.8);
    cylinder->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("cylinder", "cylinder_mat", cylinder_mat));
    m_gameworld->addGameObject(cylinder);
    */

    // create environment
    MapGenerator::restartGenerator();
    std::shared_ptr<MapSegment> map_seg0 = MapGenerator::createMap(1);
    std::shared_ptr<MapSegment> map_seg1 = MapGenerator::createMap(2);
    std::shared_ptr<MapSegment> map_seg2 = MapGenerator::createMap(3);

    std::shared_ptr<GameObject> environment = std::make_shared<GameObject>("environment");
    //environment->addComponent<TransformComponent>(std::make_shared<TransformComponent>(glm::vec3(0,0,0), 1.0));
    environment->addComponent<DungeonEnvironmentComponent>(std::make_shared<DungeonEnvironmentComponent>(7.0, ":/images/terrain.png"));
    m_gameworld->addGameObject(environment);
    // we must add the environment to the gameworld before the environment adds chunks to the gameworld
    environment->getComponent<DungeonEnvironmentComponent>()->enqueueDungeonChunksFromMapSegment(0, map_seg0);
    environment->getComponent<DungeonEnvironmentComponent>()->enqueueDungeonChunksFromMapSegment(1, map_seg1);
    environment->getComponent<DungeonEnvironmentComponent>()->enqueueDungeonChunksFromMapSegment(2, map_seg2);
    m_gameworld->getSystem<ChunkStreamingSystem>()->buildAllEnqueuedChunks();

    // create cube enemy
    std::shared_ptr<GameObject> cube = std::make_shared<GameObject>("cube_npc");
    cube->addComponent<DynamicAABCollisionComponent>(std::make_shared<DynamicAABCollisionComponent>(false, true, glm::vec3(1,1,1)));
    cube->addComponent<DungeonEnemyAIComponent>(std::make_shared<DungeonEnemyAIComponent>(map_seg0));
    cube->getComponent<TransformComponent>()->setPos(glm::vec3(35,1,22));
    cube->getComponent<TransformComponent>()->setScale(2.0f);
    Material cube_mat;
    cube_mat.color = glm::vec3(.8,.4,.3);
    cube->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("cube", "cube_mat", cube_mat));
    m_gameworld->addGameObject(cube);
}
