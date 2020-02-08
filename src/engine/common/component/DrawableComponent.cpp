#include "DrawableComponent.h"
#include "TransformComponent.h"
#include "src/engine/common/system/DrawSystem.h"

DrawableComponent::DrawableComponent(std::shared_ptr<GameObject> gameobject, std::string geometry,
                                     std::string matname, Material material) :
    Component("DrawableComponent", gameobject),
    m_material(material),
    m_matname(matname),
    m_geometry(geometry)
{
    g = Graphics::getGlobalInstance();
    g->addMaterial(m_matname, m_material);
}

DrawableComponent::~DrawableComponent()
{

}

void DrawableComponent::addGameObjectToSystems()
{
    m_gameobject->getGameWorld()->getSystem<DrawSystem>()->addComponent(getSharedPtr());
}

void DrawableComponent::removeGameObjectFromSystems() {
    m_gameobject->getGameWorld()->getSystem<DrawSystem>()->removeComponent(getSharedPtr());
}

void DrawableComponent::drawSelf() {
    g->clearTransform();
    m_gameobject->getComponent<TransformComponent>()->setObjectTransform();
    g->setMaterial(m_matname);
    g->drawShape(m_geometry);
}
