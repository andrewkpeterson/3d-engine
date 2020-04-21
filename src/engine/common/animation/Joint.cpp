#include "Joint.h"

Joint::Joint(std::string name, glm::mat4x4 local_bind_transform, std::vector<std::shared_ptr<Joint>> children) :
      m_children(children), m_name(name), m_local_bind_transform(local_bind_transform)
{
    g = Graphics::getGlobalInstance();
}

Joint::~Joint() {

}

void Joint::calcInverseBindTransform(glm::mat4x4 parent_bind_transform) {
    // parent * local
    glm::mat4x4 bind_transform = parent_bind_transform * m_local_bind_transform; // ************ check this is correct **************
    m_inverse_bind_transform = glm::inverse(bind_transform);
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->calcInverseBindTransform(bind_transform);
    }
}

void Joint::calcModelPoseTransform(glm::mat4x4 parentTotalPoseTransform) {
    // parent * local
    glm::mat4x4 total_pose_transform = parentTotalPoseTransform * m_current_local_pose_transform; // ************ check this is correct **************
    m_model_pose_transform = total_pose_transform * m_inverse_bind_transform;
    g->setShader("animation");
    g->getShader("animation")->setUniformArrayByIndex("joints", m_model_pose_transform, m_id);
    g->setShader("default");
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->calcModelPoseTransform(total_pose_transform);
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

int Joint::getId() {
    return m_id;
}
