#include "DrawSystem.h"

DrawSystem::DrawSystem(std::shared_ptr<GameWorld> gameworld) :
    System("DrawSystem", gameworld)
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
    g->setCamera(m_gameworld->getSystem<CameraSystem>()->getCurrCamComponent()->getCamera());
    auto it = m_components.begin();
    while(it != m_components.end()) {
        //it is fine to cast here because we know that only Drawable components can add themselves to the Draw System
        DrawableComponent *comp = *it;
        comp->drawSelf();
        it++;
    }
}
