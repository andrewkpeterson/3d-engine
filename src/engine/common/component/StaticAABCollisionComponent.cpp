#include "StaticAABCollisionComponent.h"
#include "DynamicAABCollisionComponent.h"
#include "TransformComponent.h"

StaticAABCollisionComponent::StaticAABCollisionComponent(bool can_move, bool active, std::vector<AAB> bounds, int layer) :
    CollisionComponent (can_move, active, layer),
    m_bounds(bounds)
{

}

StaticAABCollisionComponent::~StaticAABCollisionComponent()
{

}

void StaticAABCollisionComponent::checkCollision(CollisionComponent *comp) {
    comp->checkCollisionWithStaticAAB(this);
}

void StaticAABCollisionComponent::checkCollisionWithDynamicAAB(DynamicAABCollisionComponent *comp) {
    comp->checkCollisionWithStaticAAB(this);
}

void StaticAABCollisionComponent::checkCollisionWithStaticAAB(StaticAABCollisionComponent *that) {
    for (int this_idx = 0; this_idx < m_bounds.size(); this_idx++) {
        for (int that_idx = 0; that_idx < that->m_bounds.size(); that_idx++) {
            AAB bthis = m_bounds[this_idx];
            AAB bthat = that->m_bounds[that_idx];
            if (bthis.neg.x <= bthat.pos.x && bthis.pos.x >= bthat.neg.x) {
                if (bthis.neg.y <= bthat.pos.y && bthis.pos.y >= bthat.neg.y) {
                    if (bthis.neg.z <= bthat.pos.z && bthis.pos.z >= bthat.neg.z) {
                        std::cout << "Two static AAB components are colliding. This probably shouldn't be happening" << std::endl;
                        float xmove = 0;
                        float ymove = 0;
                        float zmove = 0;
                        float x_right = bthis.pos.x - bthat.neg.x;
                        float x_left = bthat.pos.x - bthis.neg.x;
                        if (x_right < x_left) {
                            xmove += x_right;
                        } else {
                            xmove += -x_left;
                        }
                        float y_right = bthis.pos.y - bthat.neg.y;
                        float y_left = bthat.pos.y - bthis.neg.y;
                        if (y_right < y_left) {
                            ymove += y_right;
                        } else {
                            ymove += -y_left;
                        }
                        float z_right = bthis.pos.z - bthat.neg.z;
                        float z_left = bthat.pos.z - bthis.neg.z;
                        if (z_right < z_left) {
                            zmove += z_right;
                        } else {
                            zmove += -z_left;
                        }
                        glm::vec3 mtv = glm::vec3(0,0,0);
                        if (std::abs(zmove) <= std::abs(xmove) && std::abs(zmove) <= std::abs(ymove)) {
                            mtv.z = zmove;
                        } else if (std::abs(ymove) <= std::abs(xmove) && std::abs(ymove) <= std::abs(zmove)) {
                            mtv.y = ymove;
                        } else {
                            mtv.x = xmove;
                        }
                        if (m_callback != nullptr) m_callback(Collision({that, -.5f*mtv}));
                        if (that->hasCallback()) that->callCollisionCallback(Collision({this, .5f*mtv}));
                    }
                }
            }
        }
    }
}

void StaticAABCollisionComponent::checkCollisionWithSphere(SphereCollisionComponent *that) {
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();
    for (int i = 0; i < m_bounds.size(); i++) {
        bool overlap_vertically = (m_bounds[i].neg.y < that_pos.y + that->getRadius()) && (that_pos.y - that->getRadius() < m_bounds[i].pos.y);
        glm::vec2 closest_point = glm::vec2(glm::clamp(that_pos.x, m_bounds[i].neg.x, m_bounds[i].pos.x),
                                        glm::clamp(that_pos.z, m_bounds[i].neg.z, m_bounds[i].pos.z));
        glm::vec2 that_pos2 = glm::vec2(that_pos.x, that_pos.z);
        glm::vec2 d = that_pos2 - closest_point;
        float len = glm::length(d);
        bool overlap_horizontally = len <= that->getRadius();
        if (overlap_vertically && overlap_horizontally) {
            glm::vec3 vertical_mtv;
            float a_right = m_bounds[i].pos.y - (that_pos.y - that->getRadius());
            float a_left = that_pos.y + that->getRadius() - m_bounds[i].neg.y;
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

void StaticAABCollisionComponent::translate(glm::vec3 t) {
    for (int i = 0; i < m_bounds.size(); i++) {
        m_bounds[i].neg += t;
        m_bounds[i].pos += t;
    }
}

void StaticAABCollisionComponent::checkCollisionWithCylinder(CylinderCollisionComponent *that) {
    // try to find a collision with one of this component's bounding boxes
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();
    for (int i = 0; i < m_bounds.size(); i++) {
        bool overlap_vertically = (m_bounds[i].neg.y < that_pos.y + that->getHeight()) && (that_pos.y < m_bounds[i].pos.y);
        glm::vec2 closest_point = glm::vec2(glm::clamp(that_pos.x, m_bounds[i].neg.x, m_bounds[i].pos.x),
                                        glm::clamp(that_pos.z, m_bounds[i].neg.z, m_bounds[i].pos.z));
        glm::vec2 that_pos2 = glm::vec2(that_pos.x, that_pos.z);
        glm::vec2 d = that_pos2 - closest_point;
        float len = glm::length(d);
        bool overlap_horizontally = len <= that->getRadius();
        if (overlap_vertically && overlap_horizontally) {
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

const std::vector<AAB> &StaticAABCollisionComponent::getBounds() {
    return m_bounds;
}

void StaticAABCollisionComponent::setBounds(std::vector<AAB> bounds) {
    m_bounds = bounds;
}
