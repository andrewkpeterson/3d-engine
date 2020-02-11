#include "DrawableComponent.h"
#include "TransformComponent.h"
#include "src/engine/common/system/DrawSystem.h"

DrawableComponent::DrawableComponent(std::string geometry, std::string matname, Material material) :
    Component(),
    m_material(material),
    m_matname(matname),
    m_geometry(geometry),
    shouldDraw(true)
{
    g = Graphics::getGlobalInstance();
    g->addMaterial(m_matname, m_material);
}

DrawableComponent::~DrawableComponent()
{

}

void DrawableComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<DrawSystem>()->addComponent(this);
}

void DrawableComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<DrawSystem>()->removeComponent(this);
}

void DrawableComponent::drawSelf() {
    if (shouldDraw) {
        g->clearTransform();
        m_gameobject->getComponent<TransformComponent>()->setObjectTransform();
        g->setMaterial(m_matname);
        g->drawShape(m_geometry);
    }
}

void DrawableComponent::setDraw(bool draw) {
    shouldDraw = draw;
}
