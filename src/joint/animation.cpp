#include "animation.h"

const int Animation::s_defaultLength = 60;

Animation::Animation()
  : m_length(s_defaultLength)
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
}
