#include "SphereCollisionComponent.h"
#include "TransformComponent.h"
#include "DynamicAABCollisionComponent.h"
#include "StaticAABCollisionComponent.h"

SphereCollisionComponent::SphereCollisionComponent(bool can_move, bool active, float radius, int layer) :
    CollisionComponent (can_move, active, layer),
    m_radius(radius)
{

}

SphereCollisionComponent::~SphereCollisionComponent()
{

}

void SphereCollisionComponent::checkCollision(CollisionComponent *comp) {
    comp->checkCollisionWithSphere(this);
}

void SphereCollisionComponent::checkCollisionWithDynamicAAB(DynamicAABCollisionComponent *that) {
    that->checkCollisionWithSphere(this);
}

void SphereCollisionComponent::checkCollisionWithStaticAAB(StaticAABCollisionComponent *that) {
    that->checkCollisionWithSphere(this);
}

void SphereCollisionComponent::checkCollisionWithSphere(SphereCollisionComponent *that) {
    glm::vec3 this_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();
    if (glm::length(this_pos - that_pos) < (this->m_radius + that->m_radius)) {
        glm::vec3 mtv = glm::normalize(this_pos - that_pos) * ((this->m_radius + that->m_radius) - glm::length(this_pos - that_pos));
        if (m_callback != nullptr) m_callback(Collision({that, .5f*mtv}));
        if (that->m_callback != nullptr) that->m_callback(Collision({this, -.5f*mtv}));
    }
}

void SphereCollisionComponent::checkCollisionWithCylinder(CylinderCollisionComponent *that) {
    glm::vec3 this_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();
    bool overlap_vertically = (this_pos.y - m_radius < that_pos.y + that->getHeight()) && (that_pos.y < this_pos.y + m_radius);
    glm::vec2 d = glm::vec2(this_pos.x, this_pos.z) - glm::vec2(that_pos.x, that_pos.z);
    bool overlap_horizontally = glm::length(d) < (that->getRadius() + m_radius);
    if (overlap_vertically && overlap_horizontally) {
        glm::vec3 vertical_mtv;
        float a_right = this_pos.y + m_radius - that_pos.y;
        float a_left = that_pos.y + that->getHeight() - this_pos.y;
        if (a_right < a_left) {
            vertical_mtv = glm::vec3(0,a_right,0);
        } else {
            vertical_mtv = glm::vec3(0,-a_left,0);
        }
        glm::vec2 horizontal_mtv2d = d / glm::length(d) * ((m_radius + that->getRadius()) - glm::length(d));
        glm::vec3 horizonal_mtv = glm::vec3(horizontal_mtv2d.x, 0, horizontal_mtv2d.y);
        if (glm::length(horizonal_mtv) < glm::length(vertical_mtv)) {
            if (m_callback != nullptr) m_callback(Collision({that, .5f*horizonal_mtv}));
            if (that->hasCallback()) that->callCollisionCallback(Collision({this, -.5f*horizonal_mtv}));
        } else {
            if (m_callback != nullptr) m_callback(Collision({that, -.5f*vertical_mtv}));
            if (that->hasCallback()) that->callCollisionCallback(Collision({this, .5f*vertical_mtv}));
        }
    }
}

float SphereCollisionComponent::getRadius() {
    return m_radius;
}
