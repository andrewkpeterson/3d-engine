#include "Animation.h"

Animation::Animation(std::map<std::string, std::shared_ptr<JointAnimation>> animations, float length, std::string name) :
      joint_animations(animations), time_length(length), m_name(name)
{

}

Animation::~Animation()
{

}

std::shared_ptr<JointAnimation> Animation::getJointAnimation(std::string joint_name) {
    if (joint_animations.find(joint_name) != joint_animations.end()) {
        return joint_animations[joint_name];
    } else {
        return nullptr;
    }
}

float Animation::getTimeLength() {
    return time_length;
}
