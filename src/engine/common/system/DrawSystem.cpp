#include "DrawSystem.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/component/CameraComponent.h"

DrawSystem::DrawSystem(std::shared_ptr<GameWorld> gameworld) :
    System("DrawSystem", gameworld)
{
    g = Graphics::getGlobalInstance();
}

DrawSystem::~DrawSystem()
{

}

void DrawSystem::draw(Graphics *g) {
    g->setCamera(m_gameworld->getSystem<CameraSystem>()->getCurrCamComponent()->getCamera());
    auto it = m_components.begin();
    while(it != m_components.end()) {
        //it is fine to cast here because we know that only Drawable components can add themselves to the Draw System
        std::shared_ptr<DrawableComponent> comp = std::dynamic_pointer_cast<DrawableComponent>(*it);
        comp->drawSelf();
        it++;
    }
}
