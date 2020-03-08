#include "DrawSystem.h"

DrawSystem::DrawSystem(GameWorld *gameworld) :
    System(gameworld)
{
    g = Graphics::getGlobalInstance();
}

DrawSystem::~DrawSystem()
{

}

void DrawSystem::addComponent(DrawableComponent *component) {
    m_components.insert(component);
}

void DrawSystem::removeComponent(DrawableComponent *component) {
    m_components.erase(component);
}

void DrawSystem::draw(Graphics *g) {
    std::shared_ptr<Camera> cam = m_gameworld->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera();
    g->setCamera(cam);
    auto it = m_components.begin();
    while(it != m_components.end()) {
        DrawableComponent *comp = *it;
        comp->drawSelf(cam);
        it++;
    }
}
