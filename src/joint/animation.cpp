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

  // The code messes up here
  KeyFrame *previous = iterators.first.value();
  KeyFrame *next = iterators.second.value();
  qDebug() << "Frames" << previousFrame << ">" << frame << ">" << nextFrame;
  qDebug() << "Iterators" << iterators.first.key() << iterators.second.key();
  Q_ASSERT(previous && next);

  if(nextFrame-previousFrame == 0)
    return *previous;

  qreal p = qreal(frame-previousFrame)/qreal(nextFrame-previousFrame);

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

  ConstIterator previous;
  if(next.key() < frame && !m_isLoop)
    previous = next;
  else
    previous = this->previous(next);

  return QPair<ConstIterator, ConstIterator>(previous, next);
}

Animation::ConstIterator Animation::next(ConstIterator it) const
{
  Q_ASSERT(it != end());

  if(it+1 == end())
    return m_isLoop? begin() : it;

  return it+1;
}

Animation::ConstIterator Animation::previous(ConstIterator it) const
{
  Q_ASSERT(it != end());

  if(it == begin())
    return m_isLoop? end()-1 : begin();

  return it-1;
}
