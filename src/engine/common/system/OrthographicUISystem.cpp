#include "OrthographicUISystem.h"

OrthographicUISystem::OrthographicUISystem(GameWorld *gameworld) :
    System(gameworld),
    orthographic_camera(std::make_shared<Camera>())
{
    g = Graphics::getGlobalInstance();
    orthographic_camera->setUI(true);
}

OrthographicUISystem::~OrthographicUISystem()
{

}

void OrthographicUISystem::resizeCamera(int width, int height) {
    orthographic_camera->setScreenSize(glm::vec2(width,height));
}

void OrthographicUISystem::addComponent(OrthographicUIComponent *component) {
    m_components.insert(component);
}

void OrthographicUISystem::removeComponent(OrthographicUIComponent *component) {
    m_components.erase(component);
}

void OrthographicUISystem::draw(Graphics *g) {
    std::shared_ptr<Camera> main_camera = m_gameworld->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera();
    g->setCamera(orthographic_camera);
    auto it = m_components.begin();
    while(it != m_components.end()) {
        OrthographicUIComponent *comp = *it;
        comp->drawSelf(main_camera);
        it++;
    }
}
