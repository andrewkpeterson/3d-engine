#ifndef JOINT_H
#define JOINT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <memory>
#include "src/engine/graphics/Graphics.h"

class Joint
{
public:
    Joint(std::string name, glm::mat4x4 local_bind_transform, std::vector<std::shared_ptr<Joint>> children);
    ~Joint();
    void calcInverseBindTransform(glm::mat4x4 parent_bind_transform);
    void calcModelPoseTransform(glm::mat4x4 parentModelPoseTransform);
    void setCurrentLocalPoseTransform(glm::mat4x4 mat);
    glm::mat4x4 getLocalBindTransform();
    void setID(int id);
    int getId();

private:
    std::vector<std::shared_ptr<Joint>> m_children;
    int m_id;
    std::string m_name;
    glm::mat4x4 m_model_pose_transform; // takes a vertex in model space in the bind pose and outputs a vertex in model space in a different pose.
                                        // this is what we pass into the vertex shader, and it must be recomputed every frame
    glm::mat4x4 m_current_local_pose_transform; // transform of joint in relation to its parent in current pose, taken from animation file
    glm::mat4x4 m_local_bind_transform; // transform of joint in relation to its parent in bind pose, taken from animation file
    glm::mat4x4 m_inverse_bind_transform; // inverse of product of m_local_bind_transform with the m_local_bind_tranform matrices of its ancestors,
                                          // takes a point in model space coordinates and outputs the same point in the local space of joint J
    Graphics *g;
};

#endif // JOINT_H
