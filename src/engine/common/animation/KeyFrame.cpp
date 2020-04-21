#include "KeyFrame.h"

KeyFrame::KeyFrame(std::shared_ptr<JointTransform> transform, float time_stamp) :
      m_transform(transform), m_time_stamp(time_stamp)
{

}

KeyFrame::~KeyFrame()
{

}

std::shared_ptr<JointTransform> KeyFrame::getTransform() {
    return m_transform;
}

float KeyFrame::getTimeStamp() {
    return m_time_stamp;
}
