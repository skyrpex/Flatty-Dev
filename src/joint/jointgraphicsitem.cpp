#include "jointgraphicsitem.h"
#include <QBrush>
#include <QPen>
#include <QDebug>

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

  setEnabled(false);
}

void JointGraphicsItem::setCurrentFrameData(FrameData *frameData)
{
  m_frameData = frameData;

  if(m_frameData)
    m_displayFrameData = *m_frameData;

  setEnabled(m_frameData);
}

FrameData *JointGraphicsItem::currentFrameData() const
{
  return m_frameData;
}

void JointGraphicsItem::setCurrentDisplayFrameData(const FrameData &frameData)
{
  m_frameData = NULL;
  m_displayFrameData = frameData;

  setEnabled(false);
}

FrameData JointGraphicsItem::currentDisplayFrameData() const
{
  return m_displayFrameData;
}
