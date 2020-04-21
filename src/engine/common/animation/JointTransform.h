#ifndef JOINTTRANSFORM_H
#define JOINTTRANSFORM_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <memory>

/**
 * Tranformation of joint (in relation to its parent) to describe a pose.
 */
class JointTransform
{
public:
    JointTransform(glm::vec3 pos, glm::vec4 quaternion);
    ~JointTransform();
    static glm::mat4x4 quaternion2RotationMatrix(glm::vec4 &quaternion);
    static glm::mat4x4 position2TranslationMatrix(glm::vec3 &pos);
    static glm::vec4 rotationMatrix2Quaternion(glm::mat4x4 &mat);
    static glm::vec4 quaternionInterpolationLinear(glm::vec4 start, glm::vec4 finish, float t);
    static glm::vec3 positionInterpolationLinear(glm::vec3 start, glm::vec3 finish, float t);
    static float calculateT(float start_time, float end_time, float mid_time);
    glm::vec3 getPos();
    glm::vec4 getQuat();

private:
    glm::vec3 m_pos;
    glm::vec4 m_quaternion;
};

#endif // JOINTTRANSFORM_H
