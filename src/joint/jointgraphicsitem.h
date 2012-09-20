#ifndef JOINTGRAPHICSITEM_H
#define JOINTGRAPHICSITEM_H

#include <QGraphicsEllipseItem>
#include <joint/framedata.h>

class JointGraphicsItem : public QGraphicsEllipseItem
{
public:
  JointGraphicsItem();

  void setCurrentFrameData(FrameData *currentFrameData);
  FrameData *currentFrameData() const;

  void setCurrentDisplayFrameData(const FrameData &currentFrameData);
  FrameData currentDisplayFrameData() const;

private:
  FrameData *m_frameData;
  FrameData m_displayFrameData;
};

#endif // JOINTGRAPHICSITEM_H
