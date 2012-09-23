#ifndef TIMELINEEDITOR_H
#define TIMELINEEDITOR_H

#include <QxTimeLineEditor>
#include <QMap>
#include <QString>
#include <animation/animation.h>
#include <QGraphicsLineItem>

class TimeLineEditor : public QxTimeLineEditor
{
  Q_OBJECT
public:
  TimeLineEditor(QWidget *parent = 0);

  void setAnimation(Animation *animation);

public slots:
  void setCurrentFrame(int frame);

signals:
  void currentFrameChanged(int frame);

protected:
  void contextMenuEvent(QContextMenuEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  bool addKeyFrame(int frame);
  bool removeKeyFrame(int frame);
  bool replaceKeyFrame(int from, int to);

private:
  Animation *m_animation;
  QGraphicsLineItem *m_marker;
  int m_currentFrame;
};

#endif // TIMELINEEDITOR_H
