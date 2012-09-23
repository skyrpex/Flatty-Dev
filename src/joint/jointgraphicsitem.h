#ifndef JOINTGRAPHICSITEM_H
#define JOINTGRAPHICSITEM_H

#include <QGraphicsEllipseItem>
#include <animation/keyframe.h>

class JointGraphicsItem : public QGraphicsEllipseItem
{
public:
  JointGraphicsItem();

  void setCurrentKeyFrame(KeyFrame *keyFrame);
  KeyFrame *currentKeyFrame() const;

  void setCurrentDisplayKeyFrame(const KeyFrame &currentKeyFrame);
  KeyFrame currentDisplayKeyFrame() const;

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
  KeyFrame *m_keyFrame;
  KeyFrame m_displayKeyFrame;
};

#endif // JOINTGRAPHICSITEM_H
