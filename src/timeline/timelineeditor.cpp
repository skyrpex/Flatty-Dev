#include "timelineeditor.h"
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QDebug>

TimeLineEditor::TimeLineEditor(QWidget *parent) :
  QxTimeLineEditor(parent)
{
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

void TimeLineEditor::contextMenuEvent(QContextMenuEvent *event)
{
  // We want to keep the first frame
  if(frameAt(event->pos()) > 0)
    QxTimeLineEditor::contextMenuEvent(event);
}

void TimeLineEditor::mousePressEvent(QMouseEvent *event)
{
  // We want to keep the first frame
  if(frameAt(event->pos()) > 0)
    QxTimeLineEditor::mousePressEvent(event);
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
