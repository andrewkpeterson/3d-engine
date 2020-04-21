#include "JointAnimation.h"

JointAnimation::JointAnimation(std::vector<std::shared_ptr<KeyFrame>> keyframes, float time_length) :
      m_keyframes(keyframes), m_time_length(time_length)
{

}

JointAnimation::~JointAnimation()
{

}

std::pair<std::shared_ptr<KeyFrame>, std::shared_ptr<KeyFrame>> JointAnimation::getPrevAndNextFrames(float time) {
    for (int i = 0; i < m_keyframes.size(); i++) {
        if (i < m_keyframes.size() - 1) {
            if (m_keyframes[i]->getTimeStamp() < time && time < m_keyframes[i+1]->getTimeStamp()) {
                return std::make_pair(m_keyframes[i], m_keyframes[i+1]);
            }
        } else {
            return std::make_pair(m_keyframes[m_keyframes.size()-1], m_keyframes[0]);
        }
    }
}
