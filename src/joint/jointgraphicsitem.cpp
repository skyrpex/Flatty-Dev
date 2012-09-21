#include "jointgraphicsitem.h"
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

static const int HALF_WIDTH = 10;
static const QBrush JOINT_BRUSH(Qt::white);
static const QPen JOINT_PEN(Qt::black, 3);

JointGraphicsItem::JointGraphicsItem()
  : QGraphicsEllipseItem(-HALF_WIDTH, -HALF_WIDTH, HALF_WIDTH*2, HALF_WIDTH*2)
  , m_keyFrame(NULL)
{
  setBrush(JOINT_BRUSH);
  setPen(JOINT_PEN);
  setFlags(ItemIsMovable
           | ItemIgnoresTransformations);

  setEnabled(false);
}

void JointGraphicsItem::setCurrentKeyFrame(KeyFrame *keyFrame)
{
  m_keyFrame = keyFrame;

  if(m_keyFrame)
    m_displayKeyFrame = *m_keyFrame;
  else
    m_displayKeyFrame = KeyFrame();

  setPos(m_displayKeyFrame.rotation, m_displayKeyFrame.scale);

  setEnabled(m_keyFrame);
}

KeyFrame *JointGraphicsItem::currentKeyFrame() const
{
  return m_keyFrame;
}

void JointGraphicsItem::setCurrentDisplayKeyFrame(const KeyFrame &frameData)
{
  m_keyFrame = NULL;
  m_displayKeyFrame = frameData;

  setPos(m_displayKeyFrame.rotation, m_displayKeyFrame.scale);

  setEnabled(false);
}

KeyFrame JointGraphicsItem::currentDisplayKeyFrame() const
{
  return m_displayKeyFrame;
}

void JointGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsEllipseItem::mouseMoveEvent(event);

  if(m_keyFrame)
  {
    m_keyFrame->rotation = x();
    m_keyFrame->scale = y();
  }
}
