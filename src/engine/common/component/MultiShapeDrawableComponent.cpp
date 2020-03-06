#include "MultiShapeDrawableComponent.h"
#include "TransformComponent.h"

MultiShapeDrawableComponent::MultiShapeDrawableComponent(std::vector<std::string> geometry, std::vector<std::string> matname,
                                                         std::vector<bool> should_draw_comp) :
    DrawableComponent(),
    m_matnames(matname),
    m_shapes(geometry)
{
    g = Graphics::getGlobalInstance();
}


MultiShapeDrawableComponent::~MultiShapeDrawableComponent()
{

}

void MultiShapeDrawableComponent::drawSelf() {
    if (shouldDraw) {
        for (int i = 0; i < m_matnames.size(); i++) {
            if (m_should_draw_comp[i]) {
                g->clearTransform();
                m_gameobject->getComponent<TransformComponent>()->setObjectTransform();
                g->setMaterial(m_matnames[i]);
                g->drawShape(m_shapes[i]);
            }
        }
    }
}
