#ifndef ANIMATION_H
#define ANIMATION_H

#include "KeyFrame.h"
#include "JointAnimation.h"
#include <memory>

class Animation
{
public:
    Animation(std::map<std::string, std::shared_ptr<JointAnimation>> animations, float length, std::string name, bool transition);
    ~Animation();
    std::shared_ptr<JointAnimation> getJointAnimation(std::string joint_name);
    float getTimeLength();
    std::string getName();
    bool isTransition();

private:
    std::map<std::string, std::shared_ptr<JointAnimation>> joint_animations;
    float time_length;
    std::string m_name;
    bool m_transition;
};

#endif // ANIMATION_H
