#ifndef JOINTGRAPHICSITEM_H
#define JOINTGRAPHICSITEM_H

#include <QGraphicsEllipseItem>
#include <joint/keyframe.h>

class JointGraphicsItem : public QGraphicsEllipseItem
{
public:
  JointGraphicsItem();

  void setCurrentFrameData(KeyFrame *currentFrameData);
  KeyFrame *currentFrameData() const;

  void setCurrentDisplayFrameData(const KeyFrame &currentFrameData);
  KeyFrame currentDisplayFrameData() const;

private:
  KeyFrame *m_frameData;
  KeyFrame m_displayFrameData;
};

#endif // JOINTGRAPHICSITEM_H
