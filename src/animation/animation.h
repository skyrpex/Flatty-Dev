#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QMetaType>
#include <QMap>
#include <animation/keyframe.h>
#include <QPair>

class Joint;

class Animation : public QObject, public QMap<int, KeyFrame*>
{
  Q_OBJECT
public:
  Animation(Joint *joint);

  KeyFrame displayFrameData(int frame) const;

  int length() const;
  void setLength(int length);

  Joint *joint() const;

private:
  ConstIterator iteratorNextTo(int frame) const;
  QPair<ConstIterator, ConstIterator> iteratorsAround(int frame) const;

  ConstIterator next(ConstIterator it) const;
  ConstIterator previous(ConstIterator it) const;

  Joint *m_joint;
  static const int s_defaultLength;
  int m_length;
  bool m_isLoop;
};

Q_DECLARE_METATYPE(Animation*)

#endif // ANIMATION_H
