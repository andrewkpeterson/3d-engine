#include "AABCollisionComponent.h"
#include "TransformComponent.h"

AABCollisionComponent::AABCollisionComponent(bool can_move, std::vector<AAB> bounds) :
    CollisionComponent (can_move),
    m_bounds(bounds)
{

}

AABCollisionComponent::~AABCollisionComponent()
{

}

void AABCollisionComponent::checkCollision(CollisionComponent *comp) {
    comp->checkCollisionWithAAB(this);
}

void AABCollisionComponent::checkCollisionWithAAB(AABCollisionComponent *comp) {

}

void AABCollisionComponent::checkCollisionWithSphere(SphereCollisionComponent *comp) {

}

void AABCollisionComponent::translate(glm::vec3 t) {

}

void AABCollisionComponent::checkCollisionWithCylinder(CylinderCollisionComponent *that) {
    // try to find a collision with one of this component's bounding boxes
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();
    std::cout << "check1" << std::endl;
    for (int i = 0; i < m_bounds.size(); i++) {
        std::cout << "check2" << std::endl;
        bool overlap_vertically = (m_bounds[i].neg.y < that_pos.y + that->getHeight()) && (that_pos.y < m_bounds[i].pos.y);
        glm::vec2 closest_point = glm::vec2(glm::clamp(that_pos.x, m_bounds[i].neg.x, m_bounds[i].pos.x),
                                        glm::clamp(that_pos.z, m_bounds[i].neg.z, m_bounds[i].pos.z));
        glm::vec2 that_pos2 = glm::vec2(that_pos.x, that_pos.z);
        glm::vec2 d = that_pos2 - closest_point;
        float len = glm::length(d);
        bool overlap_horizontally = len <= that->getRadius();
        if (overlap_vertically && overlap_horizontally) {
            std::cout << "collision" << std::endl;
            glm::vec3 vertical_mtv;
            float a_right = m_bounds[i].pos.y - that_pos.y;
            float a_left = that_pos.y + that->getHeight() - m_bounds[i].neg.y;
            if (a_right < a_left) {
                vertical_mtv = glm::vec3(0,a_right,0);
            } else {
                vertical_mtv = glm::vec3(0,-a_left,0);
            }

            glm::vec2 horizontal_mtv2d = (that->getRadius() - len) * glm::normalize((that_pos2 - closest_point));
            glm::vec3 horizonal_mtv = glm::vec3(horizontal_mtv2d.x, 0, horizontal_mtv2d.y);
            if (glm::length(horizonal_mtv) < glm::length(vertical_mtv)) {
                if (m_callback != nullptr) m_callback(Collision({that, -.5f*horizonal_mtv}));
                if (that->hasCallback()) that->callCollisionCallback(Collision({this, .5f*horizonal_mtv}));
            } else {
                if (m_callback != nullptr) m_callback(Collision({that, -.5f*vertical_mtv}));
                if (that->hasCallback()) that->callCollisionCallback(Collision({this, .5f*vertical_mtv}));
            }
        }
    }
}
