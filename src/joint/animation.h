#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QMetaType>
#include <QMap>
#include <joint/keyframe.h>

class Joint;

class Animation : public QObject, public QMap<int, KeyFrame*>
{
  Q_OBJECT
public:
  Animation(Joint *joint);

  KeyFrame displayFrameData(int i) const;

  int length() const;
  void setLength(int length);

  Joint *joint() const;

private:
  Joint *m_joint;
  static const int s_defaultLength;
  int m_length;
};

Q_DECLARE_METATYPE(Animation*)

#endif // ANIMATION_H
