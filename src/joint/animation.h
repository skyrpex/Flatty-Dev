#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QMetaType>
#include <QMap>
#include <joint/framedata.h>

class Animation : public QObject, public QMap<int, FrameData*>
{
  Q_OBJECT
public:
  Animation();

  FrameData displayFrameData(int i) const;

  int length() const;
  void setLength(int length);

private:
  static const int s_defaultLength;
  int m_length;
};

Q_DECLARE_METATYPE(Animation*)

#endif // ANIMATION_H
