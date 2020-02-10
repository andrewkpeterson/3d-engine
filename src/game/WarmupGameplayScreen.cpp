#include "WarmupGameplayScreen.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/PlayerControlComponent.h"
#include "src/engine/common/system/CameraSystem.h"

WarmupGameplayScreen::WarmupGameplayScreen(Graphics *g, WarmupApplication *parent_app) :
    Screen(parent_app)
{
    initializeGameWorld();
}

WarmupGameplayScreen::~WarmupGameplayScreen() {
}

void WarmupGameplayScreen::initializeGameWorld() {
    m_gameworld->addSystem<DrawSystem>(std::make_shared<DrawSystem>(m_gameworld.get()));
    m_gameworld->addSystem<TickSystem>(std::make_shared<TickSystem>(m_gameworld.get()));
    m_gameworld->addSystem<ControlCallbackSystem>(std::make_shared<ControlCallbackSystem>(m_gameworld.get()));
    m_gameworld->addSystem<CollisionSystem>(std::make_shared<CollisionSystem>(m_gameworld.get()));
    m_gameworld->addSystem<CameraSystem>(std::make_shared<CameraSystem>(m_gameworld.get()));

    //make floor
    std::shared_ptr<GameObject> floor = std::make_shared<GameObject>(m_gameworld.get());
    floor->addComponent<TransformComponent>(std::make_shared<TransformComponent>(floor.get(), glm::vec3(0,0,0), 20.0));
    Material floor_mat;
    floor_mat.textureName = "grass";
    floor_mat.textureRepeat = glm::vec2(10,10);
    floor->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(floor.get(), "quad", "grassTexture", floor_mat));
    m_gameworld->addGameObject(floor);

    //make camera
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>(m_gameworld.get());
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(player.get(), glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<PlayerControlComponent>(std::make_shared<PlayerControlComponent>(player.get()));
    player->addComponent<TransformComponent>(std::make_shared<TransformComponent>(player.get(), glm::vec3(0,0,0), 2.0));
    Material player_mat;
    player->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(player.get(), "cylinder", "playerMat", player_mat));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrCamComponent(player->getComponent<CameraComponent>().get());

}

