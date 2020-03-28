#include "PlatformerGameplayScreen.h"
#include "src/engine/common/map/MapGenerator.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/ChunkDrawableComponent.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/CylinderCollisionComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/ui/UI.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/engine/common/ui/UIShape.h"
#include "src/engine/common/component/DynamicAABCollisionComponent.h"
#include "src/engine/common/system/ChunkStreamingSystem.h"
#include "src/engine/graphics/ResourceLoader.h"
#include "src/engine/common/component/OrthographicUITextComponent.h"
#include "src/engine/common/component/UIComponent.h"
#include "src/engine/common/component/EnvironmentComponent.h"
#include "src/engine/common/system/EnvironmentSystem.h"
#include "src/platformer/PlatformerPlayerControlComponent.h"
#include "src/engine/common/component/EllipsoidComponent.h"

PlatformerGameplayScreen::PlatformerGameplayScreen(Application *parent) :
    Screen(parent)
{
    initializeGameWorld();
}

PlatformerGameplayScreen::~PlatformerGameplayScreen()
{

}

void PlatformerGameplayScreen::initializeGameWorld() {
    Graphics *g = Graphics::getGlobalInstance();

    // create environment
    std::shared_ptr<GameObject> environment = std::make_shared<GameObject>("environment");
    environment->addComponent<EnvironmentComponent>(std::make_shared<EnvironmentComponent>(":/meshes/level_easy.obj", "env_mat",
                                                                                           ":images/level_easy.png",
                                                                                           ":/meshes/level_easy.obj"));
    m_gameworld->getSystem<EnvironmentSystem>()->setEnvironment(environment->getComponent<EnvironmentComponent>());
    m_gameworld->addGameObject(environment);

    // create player
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("player");
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(glm::vec3(0,0,0), glm::vec3(0,0,1)));
    player->addComponent<PlatformerPlayerControlComponent>(std::make_shared<PlatformerPlayerControlComponent>());
    player->addComponent<EllipsoidComponent>(std::make_shared<EllipsoidComponent>(glm::vec3(.5,.5,.5)));
    player->getComponent<TransformComponent>()->setPos(glm::vec3(0,4,0));
    Material player_mat;
    player_mat.color = glm::vec3(.4,.3,.8);
    player->addComponent<PrimitiveDrawableComponent>
            (std::make_shared<PrimitiveDrawableComponent>("cube", "player_mat", player_mat));
    m_gameworld->addGameObject(player);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(player->getComponent<CameraComponent>().get());
}
