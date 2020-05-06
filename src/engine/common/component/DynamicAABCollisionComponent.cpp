#include "DynamicAABCollisionComponent.h"
#include "TransformComponent.h"
#include "StaticAABCollisionComponent.h"

DynamicAABCollisionComponent::DynamicAABCollisionComponent(bool can_move, bool active, glm::vec3 sides, int layer) :
    CollisionComponent(can_move, active, layer),
    m_sides(sides)
{

}

DynamicAABCollisionComponent::~DynamicAABCollisionComponent()
{

}

void DynamicAABCollisionComponent::checkCollision(CollisionComponent *comp) {
    comp->checkCollisionWithDynamicAAB(this);
}

void DynamicAABCollisionComponent::checkCollisionWithCylinder(CylinderCollisionComponent *that) {
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();
    glm::vec3 this_pos = getGameObject()->getComponent<TransformComponent>()->getPos();
    bool overlap_vertically = (this_pos.y - m_sides.y / 2.0f < that_pos.y + that->getHeight())
                              && (that_pos.y < this_pos.y + m_sides.y / 2.0f);
    glm::vec2 closest_point = glm::vec2(glm::clamp(that_pos.x, this_pos.x - m_sides.x / 2.0f, this_pos.x + m_sides.x / 2.0f),
                                    glm::clamp(that_pos.z, this_pos.z - m_sides.z / 2.0f, this_pos.z + m_sides.z / 2.0f));
    glm::vec2 that_pos2 = glm::vec2(that_pos.x, that_pos.z);
    glm::vec2 d = that_pos2 - closest_point;
    float len = glm::length(d);
    bool overlap_horizontally = len <= that->getRadius();
    if (overlap_vertically && overlap_horizontally) {
        glm::vec3 vertical_mtv;
        float a_right = this_pos.y + m_sides.y / 2.0f - that_pos.y;
        float a_left = that_pos.y + that->getHeight() - (this_pos.y - m_sides.y / 2.0f);
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

void DynamicAABCollisionComponent::checkCollisionWithDynamicAAB(DynamicAABCollisionComponent *that) {
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();
    glm::vec3 this_pos = getGameObject()->getComponent<TransformComponent>()->getPos();
    float thatxneg = that_pos.x - that->m_sides.x;
    float thatyneg = that_pos.y - that->m_sides.y;
    float thatzneg = that_pos.z - that->m_sides.z;
    float thatxpos = that_pos.x + that->m_sides.x;
    float thatypos = that_pos.y + that->m_sides.y;
    float thatzpos = that_pos.z + that->m_sides.z;
    float thisxneg = this_pos.x - this->m_sides.x;
    float thisyneg = this_pos.y - this->m_sides.y;
    float thiszneg = this_pos.z - this->m_sides.z;
    float thisxpos = this_pos.x + this->m_sides.x;
    float thisypos = this_pos.y + this->m_sides.y;
    float thiszpos = this_pos.z + this->m_sides.z;
    if (thisxneg <= thatxpos && thisxpos >= thatxneg) {
        if (thisyneg <= thatypos && thisypos >= thatyneg) {
            if (thiszneg <= thatzpos && thiszpos >= thatzneg) {
                float xmove = 0;
                float ymove = 0;
                float zmove = 0;
                float x_right = thisxpos - thatxneg;
                float x_left = thatxpos - thisxneg;
                if (x_right < x_left) {
                    xmove += x_right;
                } else {
                    xmove += -x_left;
                }
                float y_right = thisypos - thatyneg;
                float y_left = thatypos - thisyneg;
                if (y_right < y_left) {
                    ymove += y_right;
                } else {
                    ymove += -y_left;
                }
                float z_right = thiszpos - thatzneg;
                float z_left = thatzpos - thiszneg;
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

void DynamicAABCollisionComponent::checkCollisionWithSphere(SphereCollisionComponent *that) {
    glm::vec3 that_pos = that->getGameObject()->getComponent<TransformComponent>()->getPos();
    glm::vec3 this_pos = getGameObject()->getComponent<TransformComponent>()->getPos();
    bool overlap_vertically = (this_pos.y - m_sides.y / 2.0f < that_pos.y + that->getRadius())
                              && (that_pos.y - that->getRadius() < this_pos.y + m_sides.y / 2.0f);
    glm::vec2 closest_point = glm::vec2(glm::clamp(that_pos.x, this_pos.x - m_sides.x / 2.0f, this_pos.x + m_sides.x / 2.0f),
                                    glm::clamp(that_pos.z, this_pos.z - m_sides.z / 2.0f, this_pos.z + m_sides.z / 2.0f));
    glm::vec2 that_pos2 = glm::vec2(that_pos.x, that_pos.z);
    glm::vec2 d = that_pos2 - closest_point;
    float len = glm::length(d);
    bool overlap_horizontally = len <= that->getRadius();
    if (overlap_vertically && overlap_horizontally) {
        glm::vec3 vertical_mtv;
        float a_right = this_pos.y + m_sides.y / 2.0f - (that_pos.y - that->getRadius());
        float a_left = that_pos.y + that->getRadius() - (this_pos.y - m_sides.y / 2.0f);
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

void DynamicAABCollisionComponent::checkCollisionWithStaticAAB(StaticAABCollisionComponent *that) {
    glm::vec3 this_pos = getGameObject()->getComponent<TransformComponent>()->getPos();
    const std::vector<AAB> bounds = that->getBounds();
    float thisxneg = this_pos.x - this->m_sides.x;
    float thisyneg = this_pos.y - this->m_sides.y;
    float thiszneg = this_pos.z - this->m_sides.z;
    float thisxpos = this_pos.x + this->m_sides.x;
    float thisypos = this_pos.y + this->m_sides.y;
    float thiszpos = this_pos.z + this->m_sides.z;
    for (int that_idx = 0; that_idx < bounds.size(); that_idx++) {
        AAB bthat = bounds[that_idx];
        if (thisxneg <= bthat.pos.x && thisxpos >= bthat.neg.x) {
            if (thisyneg <= bthat.pos.y && thisypos >= bthat.neg.y) {
                if (thiszneg <= bthat.pos.z && thiszpos >= bthat.neg.z) {
                    float xmove = 0;
                    float ymove = 0;
                    float zmove = 0;
                    float x_right = thisxpos - bthat.neg.x;
                    float x_left = bthat.pos.x - thisxneg;
                    if (x_right < x_left) {
                        xmove += x_right;
                    } else {
                        xmove += -x_left;
                    }
                    float y_right = thisypos - bthat.neg.y;
                    float y_left = bthat.pos.y - thisyneg;
                    if (y_right < y_left) {
                        ymove += y_right;
                    } else {
                        ymove += -y_left;
                    }
                    float z_right = thiszpos - bthat.neg.z;
                    float z_left = bthat.pos.z - thiszneg;
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
