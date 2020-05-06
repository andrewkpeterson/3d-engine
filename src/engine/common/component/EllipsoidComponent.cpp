#include "EllipsoidComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/EnvironmentSystem.h"
#include "src/engine/common/component/TransformComponent.h"

EllipsoidComponent::EllipsoidComponent(glm::vec3 radius) :
    Component(),
    m_radius(radius)
{

}

EllipsoidComponent::~EllipsoidComponent()
{

}

void EllipsoidComponent::addComponentToSystemsAndConnectComponents()
{

}

void EllipsoidComponent::removeComponentFromSystems() {

}

void EllipsoidComponent::setRadius(glm::vec3 r) {
    m_radius = r;
}


std::pair<std::vector<EllipsoidTriangleCollision>, glm::vec3> EllipsoidComponent::checkCollisionAndTranslate(glm::vec3 curr_pos,
                                                              glm::vec3 final_pos, bool should_nudge) {
    QList<OBJ::Triangle*> tris = m_gameobject->getGameWorld()->getSystem<EnvironmentSystem>()->getEnvironment()->getTriangles();
    glm::vec3 next_pos = final_pos;
    int translations = 0;
    std::vector<EllipsoidTriangleCollision> collisions;
    int max_tranlsations;
    if (should_nudge) {
        max_tranlsations = MAX_TRANSLATIONS;
    } else {
        max_tranlsations = 1;
    }
    while (translations < max_tranlsations) {
        EllipsoidTriangleCollision closest_collision;
        closest_collision.t = INFINITY;
        for (int i = 0; i < tris.size(); i++) {
            EllipsoidTriangleCollision c = checkCollisionAgainstTriangle(curr_pos, tris[i], next_pos);
            if (c.t < closest_collision.t) {
                closest_collision = c;
            }
        }
        if (closest_collision.t == INFINITY) {
            m_gameobject->getComponent<TransformComponent>()->setPos(next_pos);
            return std::make_pair(collisions, next_pos); // we can go to next pos because there was no collision
        } else {
            glm::vec3 nudge = closest_collision.normal;

            // ***********************************************************************************
            // The following code is what prevents the ellipsoid from falling through walls and the
            // floor, while not getting stuck along the walls or the floor. We must nudge the ellipsoid
            // away from the triangle using the normal of the triangle. However, we must do this without
            // nudging the triangle in such a way that it gets pushed into another triangle and falls
            // through it. This code finds a way to nudge the ellipsoid into a safe position by iteratively
            // nudging the ellipsoid and checking it against all of the triangles in the environment.
            // This method works, but it is expensive, which is why it requires "should_nudge" to be
            // set to true
            if (should_nudge) {
                bool safely_nudged = false;
                float nudge_amount = .01;
                nudge = closest_collision.normal;
                glm::vec3 pos_nudged = closest_collision.center + nudge * nudge_amount;
                glm::vec3 prev_nudge = closest_collision.normal;
                int iterations = 0;
                while (!safely_nudged && iterations < 10) {
                    EllipsoidTriangleCollision nudge_collision;
                    nudge_collision.t = INFINITY;
                    for (int i = 0; i < tris.size(); i++) {
                        EllipsoidTriangleCollision c = checkCollisionAgainstTriangle(curr_pos, tris[i], pos_nudged);
                        if (c.t < nudge_collision.t) {
                            nudge_collision = c;
                        }
                    }
                    if (nudge_collision.t == INFINITY) {
                        curr_pos = pos_nudged;
                        safely_nudged = true;
                    } else {
                        // if the nudge we moved in and the normal of the triangle we hit was the same, then something is wrong with how
                        // the collision is happening. This most likely means that you are falling into a triangle that repeatedly pushes
                        // you away from it. If this happens, we prevent ourselves from getting stuck by nudging ourselves in the
                        // OPPOSITE direction of the normal
                        if (glm::length(nudge_collision.normal - nudge) < .00001 || glm::length(nudge_collision.normal + nudge) < .00001) {
                            nudge = -nudge_collision.normal;
                        } else {
                            nudge = nudge_collision.normal;
                        }
                        pos_nudged = nudge_collision.center + nudge * nudge_amount;
                    }
                    nudge_amount += .1;
                    iterations++;
                }
            }

            // ****************************************************
            // final_pos is where we want to be at the end of the tick without any collisions.
            // If we collide with a triangle during the tick, then we try to move in a direction
            // orthogonal to the normal of that triangle in the direction of final_pos. This
            // direction is d_corrected.
            glm::vec3 d = final_pos - curr_pos;
            glm::vec3 d_corrected = d - glm::dot(d, closest_collision.normal) * closest_collision.normal;
            next_pos = curr_pos + d_corrected;
            closest_collision.center = curr_pos;
            collisions.push_back(closest_collision);
            translations++;
        }
    }
    m_gameobject->getComponent<TransformComponent>()->setPos(curr_pos);
    return std::make_pair(collisions, curr_pos);
}

EllipsoidTriangleCollision EllipsoidComponent::checkCollisionAgainstTriangle(glm::vec3 curr_pos,
                                                                             OBJ::Triangle *tri, glm::vec3 next_pos) {
    glm::vec3 vert0 = tri->vertices[0];
    glm::vec3 vert1 = tri->vertices[1];
    glm::vec3 vert2 = tri->vertices[2];
    EllipsoidTriangleCollision c;
    c.t = INFINITY;
    // do a distance check so that we do not test collisions against far-away triangles
    if (glm::length(curr_pos - vert0) < DISTANCE_CHECK && glm::length(curr_pos - vert1) < DISTANCE_CHECK && glm::length(curr_pos - vert2) < DISTANCE_CHECK &&
        glm::length(next_pos - vert0) < DISTANCE_CHECK && glm::length(next_pos - vert1) < DISTANCE_CHECK && glm::length(next_pos - vert2) < DISTANCE_CHECK) {
        EllipsoidTriangleCollision c0;
        c0.t = INFINITY;
        EllipsoidTriangleCollision c1;
        c1.t = INFINITY;
        EllipsoidTriangleCollision c2;
        c2.t = INFINITY;

        checkInteriorCollision(curr_pos, tri, next_pos, c0);
        checkEdgeCollisionOnTriangle(curr_pos, tri, next_pos, c1);
        checkVertexCollisionOnTriangle(curr_pos, tri, next_pos, c2);

        if (c0.t < INFINITY || c1.t < INFINITY || c2.t < INFINITY) {
            if (c0.t < c1.t && c0.t < c2.t) {
                c = c0;
            } else if (c1.t < c0.t && c1.t < c2.t) {
                c = c1;
            } else {
                c = c2;
            }
        }
    }

    return c;
}

bool EllipsoidComponent::checkInteriorCollision(glm::vec3 curr_pos, OBJ::Triangle *tri,
                                       glm::vec3 next_pos, EllipsoidTriangleCollision &c) {
    // transform all points and normal to squished space
    glm::vec3 s_pos = curr_pos / m_radius;
    glm::vec3 next_s_pos = next_pos / m_radius;
    glm::vec3 vert0 = tri->vertices[0] / m_radius;
    glm::vec3 vert1 = tri->vertices[1] / m_radius;
    glm::vec3 vert2 = tri->vertices[2] / m_radius;

    // *************************************************
    // When we squish the world by dividing by the radius, we actually
    // have to MULTIPLY by the radius for the normals.
    glm::vec3 n = glm::normalize(tri->normal * m_radius);

    // calculate closest points
    glm::vec3 curr_closest_point = s_pos - n;
    glm::vec3 future_closest_point = next_s_pos - n;
    glm::vec3 d = future_closest_point - curr_closest_point;

    // calculate intersection with triangle plane
    float t = glm::dot(vert0 - curr_closest_point, n) / glm::dot(d, n);
    glm::vec3 contact_p = curr_closest_point + t * d;
    // check that t is in [0,1], if it isn't then there is no collision
    if (t >= 0 && t <= 1) {
        if (toLeft(n, vert0, vert1, contact_p) && toLeft(n, vert1, vert2, contact_p) && toLeft(n, vert2, vert0, contact_p)) {
            c.hit = contact_p * m_radius;
            c.normal = tri->normal;
            c.center = (s_pos + t * d) * m_radius;
            c.t = t;
            c.tri_vert = tri->vertices[0];
            return true;
        }
    }

    return false;
}

bool EllipsoidComponent::toLeft(glm::vec3 n, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 p) {
    return glm::dot(glm::cross(vert2 - vert1, p - vert1), n) > 0;
}

bool EllipsoidComponent::checkEdgeCollisionOnTriangle(glm::vec3 curr_pos, OBJ::Triangle *tri,
                                   glm::vec3 next_pos, EllipsoidTriangleCollision &c) {

    glm::vec3 vert0 = tri->vertices[0];
    glm::vec3 vert1 = tri->vertices[1];
    glm::vec3 vert2 = tri->vertices[2];
    EllipsoidTriangleCollision c0;
    c0.t = INFINITY;
    EllipsoidTriangleCollision c1;
    c1.t = INFINITY;
    EllipsoidTriangleCollision c2;
    c2.t = INFINITY;

    checkEdgeCollision(curr_pos, tri, next_pos, c0, vert0, vert1);
    checkEdgeCollision(curr_pos, tri, next_pos, c1, vert1, vert2);
    checkEdgeCollision(curr_pos, tri, next_pos, c2, vert2, vert0);

    if (c0.t < INFINITY || c1.t < INFINITY || c2.t < INFINITY) {
        if (c0.t < c1.t && c0.t < c2.t) {
            c = c0;
            return true;
        } else if (c1.t < c0.t && c1.t < c2.t) {
            c = c1;
            return true;
        } else {
            c = c2;
            return true;
        }
    } else {
        return false;
    }
}

void EllipsoidComponent::checkEdgeCollision(glm::vec3 curr_pos, OBJ::Triangle *tri,
                                   glm::vec3 next_pos, EllipsoidTriangleCollision &col, glm::vec3 vert0, glm::vec3 vert1) {
    glm::vec3 a = curr_pos / m_radius;
    glm::vec3 b = next_pos / m_radius;
    glm::vec3 c = vert0 / m_radius;
    glm::vec3 d = vert1 / m_radius;

    float A = std::pow(glm::length(glm::cross(b - a, d - c)), 2);
    float B = 2.0f * glm::dot(glm::cross(b - a, d - c), glm::cross(a - c, d - c));
    float C = std::pow(glm::length(glm::cross(a - c, d - c)), 2) - std::pow(glm::length(d - c), 2);
    float discrim = B*B - 4*A*C;
    float t;
    if (discrim == 0) {
        t = -B / (2 * A);
    } else if (discrim > 0) {
        float t_plus = (-B + std::sqrt(discrim)) / (2 * A);
        if (t_plus < 0) {
            t_plus = INFINITY;
        }
        float t_minus = (-B - std::sqrt(discrim)) / (2 * A);
        if (t_minus < 0) {
            t_minus = INFINITY;
        }
        t = std::min(t_plus, t_minus);
    } else {
        return;
    }

    // check that t is in [0,1], if it isn't then there is no collision
    if (t >= 0 && t <= 1) {
        glm::vec3 contact_p = a + t * (b - a);
        float dot = glm::dot(contact_p - c, d - c);
        if (dot > 0 && dot < std::pow(glm::length(d - c), 2.0)) {
            // col.hit is not quite right, because the position the ellipsoid was in during the collision is not exactly the point of collision
            col.hit = contact_p * m_radius;
            col.normal = tri->normal;
            col.center = contact_p * m_radius;
            col.t = t;
            col.tri_vert = tri->vertices[0];
        }
    }

    return;
}

bool EllipsoidComponent::checkVertexCollisionOnTriangle(glm::vec3 curr_pos, OBJ::Triangle *tri,
                                               glm::vec3 next_pos, EllipsoidTriangleCollision &c) {
    glm::vec3 vert0 = tri->vertices[0];
    glm::vec3 vert1 = tri->vertices[1];
    glm::vec3 vert2 = tri->vertices[2];
    EllipsoidTriangleCollision c0;
    c0.t = INFINITY;
    EllipsoidTriangleCollision c1;
    c1.t = INFINITY;
    EllipsoidTriangleCollision c2;
    c2.t = INFINITY;

    checkVertexCollision(curr_pos, tri, next_pos, c0, vert0);
    checkVertexCollision(curr_pos, tri, next_pos, c1, vert1);
    checkVertexCollision(curr_pos, tri, next_pos, c2, vert2);

    if (c0.t < INFINITY || c1.t < INFINITY || c2.t < INFINITY) {
        if (c0.t < c1.t && c0.t < c2.t) {
            c = c0;
            return true;
        } else if (c1.t < c0.t && c1.t < c2.t) {
            c = c1;
            return true;
        } else {
            c = c2;
            return true;
        }
    } else {
        return false;
    }
}

void EllipsoidComponent::checkVertexCollision(glm::vec3 curr_pos, OBJ::Triangle *tri,
                                     glm::vec3 next_pos, EllipsoidTriangleCollision &c, glm::vec3 vert) {
    glm::vec3 s_pos = glm::vec3(0,0,0);
    glm::vec3 v = (vert - curr_pos) / m_radius;
    glm::vec3 next_s_pos = (next_pos - curr_pos) / m_radius;
    glm::vec3 d = -(next_pos - curr_pos) / m_radius;
    float A = d.x*d.x + d.y*d.y + d.z*d.z;
    float B = 2*v.x*d.x + 2*v.y*d.y + 2*v.z*d.z;
    float C = v.x*v.x + v.y*v.y + v.z*v.z - 1.0f;
    float discrim = B*B - 4*A*C;
    float t;
    if (discrim == 0) {
        t = -B / (2 * A);
    } else if (discrim > 0) {
        float t_plus = (-B + std::sqrt(discrim)) / (2 * A);
        if (t_plus < 0) {
            t_plus = INFINITY;
        }
        float t_minus = (-B - std::sqrt(discrim)) / (2 * A);
        if (t_minus < 0) {
            t_minus = INFINITY;
        }
        t = std::min(t_plus, t_minus);
    } else {
        return;
    }

    // check that t is in [0,1], if it isn't then there is no collision
    if (t >= 0 && t <= 1) {
        glm::vec3 contact_p = curr_pos + t * (next_pos - curr_pos); // contact p is the center of the ellipsoid at time of collision
        c.hit = contact_p; // c.hit is not quite right, because the position the ellipsoid was in during the collision is not exactly the point of collision
        c.normal = tri->normal;
        c.center = contact_p;
        c.t = t;
        c.tri_vert = tri->vertices[0];
    }

    return;
}
