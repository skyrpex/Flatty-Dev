#include "jointgraphicsitem.h"

JointGraphicsItem::JointGraphicsItem()
  : m_frameData(NULL)
{
}

void JointGraphicsItem::setFrameData(FrameData *frameData)
{
  if(frameData)
    setDisplayFrameData(*frameData);

  m_frameData = frameData;
}

FrameData *JointGraphicsItem::frameData() const
{
  return m_frameData;
}

void JointGraphicsItem::setDisplayFrameData(const FrameData &frameData)
{
  m_frameData = NULL;
  m_displayFrameData = frameData;
}

FrameData JointGraphicsItem::displayFrameData() const
{
  return m_displayFrameData;
}
