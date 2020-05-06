#include "Animation.h"

Animation::Animation(std::map<std::string, std::shared_ptr<JointAnimation>> animations, float length, std::string name, bool transition) :
      joint_animations(animations), time_length(length), m_name(name), m_transition(transition)
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

std::string Animation::getName() {
    return m_name;
}

bool Animation::isTransition() {
    return m_transition;
}
