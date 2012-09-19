#ifndef JOINTGRAPHICSITEM_H
#define JOINTGRAPHICSITEM_H

#include <QGraphicsEllipseItem>
#include <joint/framedata.h>

class JointGraphicsItem : public QGraphicsEllipseItem
{
public:
  JointGraphicsItem();

  void setFrameData(FrameData *frameData);
  FrameData *frameData() const;

  void setDisplayFrameData(const FrameData &frameData);
  FrameData displayFrameData() const;

private:
  FrameData *m_frameData;
  FrameData m_displayFrameData;
};

#endif // JOINTGRAPHICSITEM_H
