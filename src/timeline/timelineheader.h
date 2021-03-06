#ifndef TIMELINEHEADER_H
#define TIMELINEHEADER_H

#include <QHeaderView>

class TimeLineHeader : public QHeaderView
{
  Q_OBJECT
public:
  explicit TimeLineHeader(QWidget *parent = 0);

  int currentFrame() const;

public slots:
  void setCurrentFrame(int frame);

signals:
  void currentFrameChanged(int frame);

protected:
  void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);

private:
  void updateCurrentFrame(const QPoint &pos);

  int m_currentFrame;
};

#endif // TIMELINEHEADER_H
