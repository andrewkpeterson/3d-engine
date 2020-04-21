#include "JointTransform.h"

JointTransform::JointTransform(glm::vec3 pos, glm::vec4 quaternion) :
      m_pos(pos), m_quaternion(quaternion)
{

}

JointTransform::~JointTransform()
{

}

glm::vec3 JointTransform::getPos() {
    return m_pos;
}

glm::vec4 JointTransform::getQuat() {
    return m_quaternion;
}

glm::mat4x4 JointTransform::quaternion2RotationMatrix(glm::vec4 &quaternion) {
    quaternion = glm::normalize(quaternion);
    float qx = quaternion.x;
    float qy = quaternion.y;
    float qz = quaternion.z;
    float qw = quaternion.w;

    return glm::transpose(glm::mat4x4(1.0f - 2.0f*qy*qy - 2.0f*qz*qz, 2.0f*qx*qy - 2.0f*qz*qw, 2.0f*qx*qz + 2.0f*qy*qw, 0.0f,
                                      2.0f*qx*qy + 2.0f*qz*qw, 1.0f - 2.0f*qx*qx - 2.0f*qz*qz, 2.0f*qy*qz - 2.0f*qx*qw, 0.0f,
                                      2.0f*qx*qz - 2.0f*qy*qw, 2.0f*qy*qz + 2.0f*qx*qw, 1.0f - 2.0f*qx*qx - 2.0f*qy*qy, 0.0f,
                                      0.0f, 0.0f, 0.0f, 1.0f));
}

glm::mat4x4 JointTransform::position2TranslationMatrix(glm::vec3 &v) {
    return glm::transpose(glm::mat4x4(1.0f, 0.0f, 0.0f, v.x,
                                      0.0f, 1.0f, 0.0f, v.y,
                                      0.0f, 0.0f, 1.0f, v.z,
                                      0.0f, 0.0f, 0.0f, 1.0f));
}

glm::vec4 JointTransform::quaternionInterpolationLinear(glm::vec4 start, glm::vec4 finish, float t) {
    start = glm::normalize(start);
    finish = glm::normalize(finish);

    double cosine = glm::dot(start, finish);

    if (cosine < 0) {
        finish = -finish;
        cosine = -cosine;
    }

    if (cosine > .999) {
        glm::vec4 result = start + (finish - start) * t;
        result = glm::normalize(result);
        return result;
    }

    float theta_0 = glm::acos(cosine);
    float theta = theta_0*t;
    float sin_theta = glm::sin(theta);
    float sin_theta_0 = glm::sin(theta_0);
    float s0 = glm::cos(theta) - cosine * sin_theta / sin_theta_0;
    float s1 = sin_theta / sin_theta_0;

    glm::vec4 result = (s0 * start) + (s1 * finish);
    return glm::normalize(result);
}

glm::vec3 JointTransform::positionInterpolationLinear(glm::vec3 start, glm::vec3 finish, float t) {
    return start + (finish - start) * t;
}

float JointTransform::calculateT(float start_time, float end_time, float mid_time) {
    return (mid_time - start_time)  / (end_time - start_time);
}
