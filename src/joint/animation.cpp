#include "animation.h"

const int Animation::s_defaultLength = 60;

Animation::Animation(Joint *joint)
  : m_joint(joint),
    m_length(s_defaultLength)
{
  insert(0, new FrameData);
}

FrameData Animation::displayFrameData(int i) const
{
  return FrameData();
}

int Animation::length() const
{
  return qMax(keys().last(), m_length);
}

void Animation::setLength(int length)
{
  m_length = length;

  Iterator it = begin();
  while(it != end())
  {
    if(it.key() > m_length)
      it = erase(it);
    else
      ++it;
  }
}

Joint *Animation::joint() const
{
  return m_joint;
}
