#include "animation.h"
#include <QDebug>

const int Animation::s_defaultLength = 60;

Animation::Animation(Joint *joint)
  : m_joint(joint)
  , m_length(s_defaultLength)
  , m_isLoop(true)
{
  insert(0, new KeyFrame);
}

KeyFrame Animation::displayFrameData(int frame) const
{
  QPair<ConstIterator, ConstIterator> iterators = iteratorsAround(frame);

  int previousFrame = iterators.first.key();
  int nextFrame = iterators.second.key();
  if(nextFrame < previousFrame)
    nextFrame += length();

  if(nextFrame-previousFrame == 0)
    return KeyFrame();


  qreal p = qreal(frame-previousFrame)/qreal(nextFrame-previousFrame);

  // The code messes up here
  KeyFrame *previous = iterators.first.value();
  KeyFrame *next = iterators.second.value();
  qDebug() << "Frames" << previousFrame << frame << nextFrame;
  qDebug() << "Iterators" << iterators.first.key() << iterators.second.key();
  qDebug() << "Data" << (ulong)previous << (ulong)next;
  Q_ASSERT(previous && next);

  KeyFrame keyFrame;
  keyFrame.rotation = previous->rotation + p*(next->rotation-previous->rotation);
  keyFrame.scale = previous->scale + p*(next->scale-previous->scale);
  return keyFrame;
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

Animation::ConstIterator Animation::iteratorNextTo(int frame) const
{
  // Look for the first keyframe bigger than the given frame
  ConstIterator it = begin();
  while(it != end())
  {
    // If found, return
    if(it.key() > frame)
      return it;
    ++it;
  }

  // If there is no next iterator, should we loop.
  // The returned value will range from begin() to end()-1
  return m_isLoop ? begin() : end()-1;
}

QPair<Animation::ConstIterator, Animation::ConstIterator> Animation::iteratorsAround(int frame) const
{
  ConstIterator next = iteratorNextTo(frame);

  if(next == begin())
    return QPair<ConstIterator, ConstIterator>(m_isLoop? end()-1 : begin(), next);

  return QPair<ConstIterator, ConstIterator>(next-1, next);
}
