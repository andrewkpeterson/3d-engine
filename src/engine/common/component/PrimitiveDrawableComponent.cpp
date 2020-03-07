#include "PrimitiveDrawableComponent.h"
#include "DrawableComponent.h"
#include "TransformComponent.h"
#include "src/engine/common/system/DrawSystem.h"

PrimitiveDrawableComponent::PrimitiveDrawableComponent(std::string geometry, std::string matname, Material material) :
    DrawableComponent(),
    m_matname(matname),
    m_geometry(geometry)
{
    g = Graphics::getGlobalInstance();
    g->addMaterial(m_matname, material);
}

PrimitiveDrawableComponent::PrimitiveDrawableComponent(std::string geometry, std::string matname) :
    DrawableComponent(),
    m_matname(matname),
    m_geometry(geometry)
{
    g = Graphics::getGlobalInstance();
}

PrimitiveDrawableComponent::~PrimitiveDrawableComponent()
{

}

void PrimitiveDrawableComponent::drawSelf() {
    if (shouldDraw) {
        g->clearTransform();
        m_gameobject->getComponent<TransformComponent>()->setObjectToWorldTransform();
        m_gameobject->getComponent<TransformComponent>()->setObjectSpaceOrientation();
        g->setMaterial(m_matname);
        g->drawShape(m_geometry);
    }
}

void PrimitiveDrawableComponent::setMaterial(std::string matname) {
    m_matname = matname;
}

