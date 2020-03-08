#include "OrthographicUIShapeComponent.h"
#include "src/engine/graphics/Camera.h"
#include "TransformComponent.h"
#include "src/engine/common/system/OrthographicUISystem.h"

OrthographicUIShapeComponent::OrthographicUIShapeComponent(std::string geometry, std::string matname, Material material, glm::vec3 offset,
                                                           glm::vec3 size) :
    OrthographicUIComponent(matname, material, offset),
    m_geometry(geometry),
    m_size(size)
{

}

OrthographicUIShapeComponent::OrthographicUIShapeComponent(std::string geometry, std::string matname, glm::vec3 offset, glm::vec3 size) :
    OrthographicUIComponent (matname, offset),
    m_geometry(geometry),
    m_size(size)
{

}

OrthographicUIShapeComponent::~OrthographicUIShapeComponent() {

}

void OrthographicUIShapeComponent::setSize(glm::vec3 new_size) {
    m_size = new_size;
}

void OrthographicUIShapeComponent::drawSelf(std::shared_ptr<Camera> camera) {
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    glm::vec3 screen_pos = convertToScreenSpace(t->getPos() + m_offset, camera);
    if (screen_pos.z > 0) {
        if (shouldDraw) {
            g->clearTransform();
            g->setMaterial(m_matname);
            g->translate(glm::vec3(screen_pos.x, screen_pos.y, screen_pos.z));
            g->scale(m_size);
            g->drawShape(m_geometry);
        }
    }
}
