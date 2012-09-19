#ifndef TIMELINEEDITOR_H
#define TIMELINEEDITOR_H

#include <QxTimeLineEditor>
#include <QMap>
#include <QString>
#include <joint/animation.h>

class TimeLineEditor : public QxTimeLineEditor
{
public:
  TimeLineEditor(QWidget *parent = 0);

  void setAnimation(Animation *animation);

protected:
  void contextMenuEvent(QContextMenuEvent *event);
  void mousePressEvent(QMouseEvent *event);
  bool addKeyFrame(int frame);
  bool removeKeyFrame(int frame);
  bool replaceKeyFrame(int from, int to);

private:
  Animation *m_animation;
};

#endif // TIMELINEEDITOR_H
