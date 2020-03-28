#include "EnvironmentSystem.h"
#include "src/engine/graphics/Camera.h"
#include "src/engine/common/system/CameraSystem.h"

EnvironmentSystem::EnvironmentSystem(GameWorld *gameworld) :
    System(gameworld),
    environment(nullptr)
{
    g = Graphics::getGlobalInstance();
}

EnvironmentSystem::~EnvironmentSystem()
{

}

void EnvironmentSystem::setEnvironment(std::shared_ptr<EnvironmentComponent> env) {
    environment = env;
}

std::shared_ptr<EnvironmentComponent> EnvironmentSystem::getEnvironment() {
    return environment;
}

void EnvironmentSystem::drawEnvironment() {
    std::shared_ptr<Camera> cam = m_gameworld->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera();
    g->setCamera(cam);
    if (environment != nullptr) {
        environment->draw();
    }
}
