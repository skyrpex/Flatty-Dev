#include "timelineeditor.h"
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QDebug>
//#include <QPen>

static const QPen LINE_PEN(QColor(250, 0, 0), 1);
static const int LINE_OFFSET = 3;
static const int FRAME_HEIGHT = 20;

TimeLineEditor::TimeLineEditor(QWidget *parent) :
  QxTimeLineEditor(parent)
{
  m_marker = new QGraphicsLineItem(LINE_OFFSET, 0, LINE_OFFSET, FRAME_HEIGHT, NULL, scene());
  m_marker->setZValue(1);
  m_marker->setPen(LINE_PEN);
}

void TimeLineEditor::setAnimation(Animation *animation)
{
  m_animation = animation;

  if(animation)
  {
    setMaximumFrameCount(animation->length());
    setKeyFrames(animation->keys());
  }
  else
  {
    setKeyFrames(QList<int>());
    setMaximumFrameCount(60);
  }

  setEnabled(animation);
}

void TimeLineEditor::setCurrentFrame(int frame)
{
  if(m_currentFrame != frame)
  {
    m_currentFrame = frame;
    emit currentFrameChanged(frame);
    m_marker->setPos(frame*8, 0);
  }
}

void TimeLineEditor::contextMenuEvent(QContextMenuEvent *event)
{
  // We want to keep the first frame
  int frame = frameAt(event->pos());
  if(frame > 0)
    QxTimeLineEditor::contextMenuEvent(event);
  setCurrentFrame(frame);
}

void TimeLineEditor::mousePressEvent(QMouseEvent *event)
{
  // We want to keep the first frame
  int frame = frameAt(event->pos());
  if(frame > 0)
    QxTimeLineEditor::mousePressEvent(event);

  setCurrentFrame(frame);
}

void TimeLineEditor::mouseMoveEvent(QMouseEvent *event)
{
  QxTimeLineEditor::mouseMoveEvent(event);
  setCurrentFrame(frameAt(event->pos()));
}

bool TimeLineEditor::addKeyFrame(int frame)
{
  m_animation->insert(frame, new FrameData);
  return true;
}

bool TimeLineEditor::removeKeyFrame(int frame)
{
  delete m_animation->take(frame);
  return true;
}

bool TimeLineEditor::replaceKeyFrame(int from, int to)
{
  QMap<int, FrameData*>::Iterator it = m_animation->find(to);
  if(it != m_animation->end())
    delete m_animation->take(to);

  FrameData *keyFrame = m_animation->take(from);
  m_animation->insert(to, keyFrame);
  return true;
}
