#ifndef JOINTANIMATION_H
#define JOINTANIMATION_H

#include "KeyFrame.h"

class JointAnimation
{
public:
    JointAnimation(std::vector<std::shared_ptr<KeyFrame>> keyframes, float time_length);
    ~JointAnimation();
    std::pair<std::shared_ptr<KeyFrame>, std::shared_ptr<KeyFrame> > getPrevAndNextFrames(float time);
    std::shared_ptr<KeyFrame> getFirstFrame();

private:
    std::vector<std::shared_ptr<KeyFrame>> m_keyframes;
    float m_time_length;
};

#endif // JOINTANIMATION_H
