#include "CylinderCollisionComponent.h"
#include "TransformComponent.h"
#include "StaticAABCollisionComponent.h"
#include "DynamicAABCollisionComponent.h"

CylinderCollisionComponent::CylinderCollisionComponent(bool can_move, float radius, float height) :
    CollisionComponent(can_move),
    m_radius(radius),
    m_height(height)
{

}

CylinderCollisionComponent::~CylinderCollisionComponent()
{

}

void CylinderCollisionComponent::checkCollision(CollisionComponent *comp) {
    comp->checkCollisionWithCylinder(this);
}

void CylinderCollisionComponent::checkCollisionWithCylinder(CylinderCollisionComponent *that) {
    glm::vec3 this_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();
    bool overlap_vertically = (this_pos.y < that_pos.y + that->m_height) && (that_pos.y < this_pos.y + m_height);
    glm::vec2 d = glm::vec2(this_pos.x, this_pos.z) - glm::vec2(that_pos.x, that_pos.z);
    bool overlap_horizontally = glm::length(d) < (that->m_radius + m_radius);
    if (overlap_vertically && overlap_horizontally) {
        glm::vec3 vertical_mtv;
        float a_right = this_pos.y + m_height - that_pos.y;
        float a_left = that_pos.y + that->m_height - this_pos.y;
        if (a_right < a_left) {
            vertical_mtv = glm::vec3(0,a_right,0);
        } else {
            vertical_mtv = glm::vec3(0,-a_left,0);
        }
        glm::vec2 horizontal_mtv2d = d / glm::length(d) * ((m_radius + that->m_radius) - glm::length(d));
        glm::vec3 horizonal_mtv = glm::vec3(horizontal_mtv2d.x, 0, horizontal_mtv2d.y);
        if (glm::length(horizonal_mtv) < glm::length(vertical_mtv)) {
            if (m_callback != nullptr) m_callback(Collision({that, .5f*horizonal_mtv}));
            if (that->m_callback != nullptr) that->m_callback(Collision({this, -.5f*horizonal_mtv}));
        } else {
            if (m_callback != nullptr) m_callback(Collision({that, -.5f*vertical_mtv}));
            if (that->m_callback != nullptr) that->m_callback(Collision({this, .5f*vertical_mtv}));
        }
    }
}

void CylinderCollisionComponent::checkCollisionWithStaticAAB(StaticAABCollisionComponent *comp) {
    comp->checkCollisionWithCylinder(this);
}

void CylinderCollisionComponent::checkCollisionWithDynamicAAB(DynamicAABCollisionComponent *comp) {
    comp->checkCollisionWithCylinder(this);
}


void CylinderCollisionComponent::checkCollisionWithSphere(SphereCollisionComponent *comp) {
    comp->checkCollisionWithCylinder(this);
}

float CylinderCollisionComponent::getHeight() {
    return m_height;
}

float CylinderCollisionComponent::getRadius() {
    return m_radius;
}
