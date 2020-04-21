#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "JointTransform.h"
#include <memory>
#include <map>

class KeyFrame
{
public:
    KeyFrame(std::shared_ptr<JointTransform>, float time_stamp);
    ~KeyFrame();
    std::shared_ptr<JointTransform> getTransform();
    float getTimeStamp();

private:
    std::shared_ptr<JointTransform> m_transform;
    float m_time_stamp;
};

#endif // KEYFRAME_H
