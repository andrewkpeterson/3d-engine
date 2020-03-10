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
#include "src/engine/common/ui/UIShape.h"
#include "src/dungeon/DungeonPlayerControlComponent.h"
#include "src/engine/common/component/DynamicAABCollisionComponent.h"
#include "src/engine/common/system/ChunkStreamingSystem.h"
#include "src/dungeon/DungeonEnemyAIComponent.h"
#include "src/dungeon/SwordComponent.h"
#include "src/engine/graphics/ResourceLoader.h"
#include "src/engine/common/component/OrthographicUITextComponent.h"
#include "src/engine/common/component/UIComponent.h"

DungeonGameplayScreen::DungeonGameplayScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

DungeonGameplayScreen::~DungeonGameplayScreen()
{

}

void DungeonGameplayScreen::initializeGameWorld() {
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
                                                                      glm::vec2(20.0f,40.0f), "white", "press_start_2p");
    hud->getComponent<UIComponent>()->addElement("HEALTH", health_label);
    std::shared_ptr<UIShape> health_bar = std::make_shared<UIShape>(hud->getComponent<UIComponent>().get(), "uiquad",
                                                                    glm::vec2(20.0f,10.0f),
                                                                    glm::vec2(100,10),"health_bar_mat");
    hud->getComponent<UIComponent>()->addElement("health_bar", health_bar);
    m_gameworld->addGameObject(hud);


    // load in visual data for sword character
    std::shared_ptr<Shape> sword_shape = std::make_shared<Shape>("sword");
    ResourceLoader::readObj(":/meshes/sword.obj", sword_shape);
    Material sword_mat;
    sword_mat.textureName = "sword_texture";
    g->addMaterial("sword_mat", sword_mat);
    g->addShape("sword", sword_shape);
    g->addTexture("sword_texture", ":/images/sword.png", Texture::FILTER_METHOD::LINEAR);

    // create sword
    std::shared_ptr<GameObject> sword = std::make_shared<GameObject>("sword");
    sword->getComponent<TransformComponent>()->setPos(glm::vec3(31,1,20));
    sword->getComponent<TransformComponent>()->setScale(.1f);
    sword->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sword", "sword_mat"));
    sword->addComponent<DynamicAABCollisionComponent>(std::make_shared<DynamicAABCollisionComponent>(true, true, glm::vec3(3,3,3)));
    sword->addComponent<SwordComponent>(std::make_shared<SwordComponent>());
    m_gameworld->addGameObject(sword);

    // create player
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<DungeonPlayerControlComponent>(std::make_shared<DungeonPlayerControlComponent>());
    player->addComponent<DynamicAABCollisionComponent>(std::make_shared<DynamicAABCollisionComponent>(true, true, glm::vec3(1,1,1)));
    player->getComponent<TransformComponent>()->setPos(glm::vec3(31,1,20));
    player->getComponent<TransformComponent>()->setScale(2.0f);
    Material player_mat;
    player_mat.color = glm::vec3(.4,.3,.8);
    player->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("cube", "player_mat", player_mat));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());

    // create sphere npc
    std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>("sphere_npc");
    sphere->addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, 1.5));
    sphere->addComponent<OrthographicUITextComponent>(
                std::make_shared<OrthographicUITextComponent>("You must go into the dungeon and defeat the creepers",
                                                              "white", glm::vec3(-3,1.5,0),20.0f, "press_start_2p"));
    sphere->getComponent<TransformComponent>()->setPos(glm::vec3(28,1,20));
    sphere->getComponent<TransformComponent>()->setScale(2.0f);
    Material sphere_mat;
    sphere_mat.color = glm::vec3(.4,.8,.3);
    sphere->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "sphere_mat", sphere_mat));
    m_gameworld->addGameObject(sphere);

    /*
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
    environment->getComponent<DungeonEnvironmentComponent>()->addEnemies(0);
    environment->getComponent<DungeonEnvironmentComponent>()->addEnemies(1);
    environment->getComponent<DungeonEnvironmentComponent>()->addEnemies(2);
    m_gameworld->getSystem<ChunkStreamingSystem>()->buildAllEnqueuedChunks();

    // load in visual data for enemy
    std::shared_ptr<Shape> enemy_shape = std::make_shared<Shape>("enemy");
    ResourceLoader::readObj(":/meshes/creeper.obj", enemy_shape);
    Material enemy_mat;
    enemy_mat.textureName = "enemy_texture";
    g->addMaterial("enemy_mat", enemy_mat);
    g->addShape("enemy", enemy_shape);
    g->addTexture("enemy_texture", ":/images/creeper.jpg", Texture::FILTER_METHOD::NEAREST);

    Material damaged_mat;
    damaged_mat.color = glm::vec3(1,0,0);
    g->addMaterial("damaged_mat", damaged_mat);

}
