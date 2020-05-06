#include "Joint.h"

Joint::Joint(std::string name, glm::mat4x4 local_bind_transform, std::vector<std::shared_ptr<Joint>> children, glm::vec3 bind_pose_position) :
      m_children(children), m_name(name), m_local_bind_transform(local_bind_transform), m_bind_pose_position(bind_pose_position),
      m_current_pos_position(glm::vec4()), m_total_pose_transform(glm::mat4x4())
{
    g = Graphics::getGlobalInstance();
}

Joint::~Joint() {

}

void Joint::calcInverseBindTransform(glm::mat4x4 parent_bind_transform) {
    // parent * local
    glm::mat4x4 bind_transform = parent_bind_transform * m_local_bind_transform;
    m_inverse_bind_transform = glm::inverse(bind_transform);
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->calcInverseBindTransform(bind_transform);
    }
}


void Joint::setOffsetMatrix(glm::mat4x4 mat) {
    m_offset_mat = mat;
    m_bind_pose_position = glm::vec3(mat * glm::vec4(0,0,0,1));
}

void Joint::calcModelPoseTransform(glm::mat4x4 parentTotalPoseTransform) {
    // parent * local
    m_total_pose_transform = parentTotalPoseTransform * m_current_local_pose_transform;
    m_model_pose_transform = m_total_pose_transform * m_offset_mat;
    //m_model_pose_transform = m_total_pose_transform * m_inverse_bind_transform;
    g->setShader("animation");
    if (m_id > 10) {
        g->getShader("animation")->setUniformArrayByIndex("joints2", m_model_pose_transform, m_id % 10);
    } else {
        g->getShader("animation")->setUniformArrayByIndex("joints1", m_model_pose_transform, m_id);
    }
    //g->setShader("default");
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->calcModelPoseTransform(m_total_pose_transform);
    }
}

void Joint::setCurrentLocalPoseTransform(glm::mat4x4 mat) {
    m_current_local_pose_transform = mat;
}

void Joint::setID(int id) {
    m_id = id;
}

glm::mat4x4 Joint::getLocalBindTransform() {
    return m_local_bind_transform;
}

glm::mat4x4 Joint::getOffsetMatrix() {
    return m_offset_mat;
}

glm::mat4x4 Joint::getInverseBindTransform() {
    return m_inverse_bind_transform;
}

glm::mat4x4 Joint::getCurrentTotalPoseTransform() {
    return m_total_pose_transform;
}

int Joint::getId() {
    return m_id;
}

glm::vec3 Joint::getBindPosePosition() {
    return m_bind_pose_position;
}

glm::vec3 Joint::getCurrentPosePosition() {
    return m_current_pos_position;
}
