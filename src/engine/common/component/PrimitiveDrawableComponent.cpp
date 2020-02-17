#include "PrimitiveDrawableComponent.h"
#include "DrawableComponent.h"
#include "TransformComponent.h"
#include "src/engine/common/system/DrawSystem.h"

PrimitiveDrawableComponent::PrimitiveDrawableComponent(std::string geometry, std::string matname, Material material) :
    DrawableComponent(),
    m_material(material),
    m_matname(matname),
    m_geometry(geometry)
{
    g = Graphics::getGlobalInstance();
    g->addMaterial(m_matname, m_material);
}

PrimitiveDrawableComponent::~PrimitiveDrawableComponent()
{

}

void PrimitiveDrawableComponent::drawSelf() {
    if (shouldDraw) {
        g->clearTransform();
        m_gameobject->getComponent<TransformComponent>()->setObjectTransform();
        g->setMaterial(m_matname);
        g->drawShape(m_geometry);
    }
}

