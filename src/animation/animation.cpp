#include "animation.h"
#include <QDebug>
#include <mathhelper.h>

const int Animation::s_defaultLength = 60;
static const int DefaultFps = 60;

Animation::Animation(Joint *joint)
  : m_joint(joint)
  , m_length(s_defaultLength)
  , m_isLoop(true)
  , m_fps(DefaultFps)
{
  insert(0, new KeyFrame);
}

KeyFrame Animation::displayFrameData(int frame) const
{
  QPair<ConstIterator, ConstIterator> iterators = iteratorsAround(frame);
  ConstIterator a = previous(iterators.first);
  ConstIterator b = iterators.first;
  ConstIterator c = iterators.second;
  ConstIterator d = next(iterators.second);

  int previousFrame = b.key();
  int nextFrame = c.key();
  if(nextFrame-previousFrame == 0)
    return *b.value();

  if(nextFrame < previousFrame)
    nextFrame += length();

  qreal p = qreal(frame-previousFrame)/qreal(nextFrame-previousFrame);

  KeyFrame keyFrame;
  keyFrame.rotation = Math::catmullRomInterpolation(a.value()->rotation, b.value()->rotation,
                                                    c.value()->rotation, d.value()->rotation,
                                                    a.key(), b.key(), c.key(), d.key(),
                                                    p);
  keyFrame.scale = Math::catmullRomInterpolation(a.value()->scale, b.value()->scale,
                                                 c.value()->scale, d.value()->scale,
                                                 a.key(), b.key(), c.key(), d.key(),
                                                 p);
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

int Animation::fps() const
{
  return m_fps;
}

void Animation::setFps(int fps)
{
  m_fps = fps;
}

bool Animation::isLoop() const
{
  return m_isLoop;
}

void Animation::setIsLoop(bool loop)
{
  m_isLoop = loop;
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
