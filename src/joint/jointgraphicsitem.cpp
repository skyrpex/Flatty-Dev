#include "jointgraphicsitem.h"
#include <QBrush>
#include <QPen>

static const int HALF_WIDTH = 10;
static const QBrush JOINT_BRUSH(Qt::white);
static const QPen JOINT_PEN(Qt::black, 3);

JointGraphicsItem::JointGraphicsItem()
  : QGraphicsEllipseItem(-HALF_WIDTH, -HALF_WIDTH, HALF_WIDTH*2, HALF_WIDTH*2)
  , m_frameData(NULL)
{
  setBrush(JOINT_BRUSH);
  setPen(JOINT_PEN);
  setFlags(ItemIsMovable
           | ItemIgnoresTransformations);
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
