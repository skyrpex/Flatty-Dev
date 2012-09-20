#include "timelineheader.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QDateTime>
#include <joint/joint.h>

TimeLineHeader::TimeLineHeader(QWidget *parent) :
  QHeaderView(Qt::Horizontal, parent),
  m_currentFrame(0)
{
  // Make sure a scrollbar appears
  setResizeMode(ResizeToContents);
  setStretchLastSection(false);
}

void TimeLineHeader::setCurrentFrame(int frame)
{
  m_currentFrame = frame;
  viewport()->update();
}

void TimeLineHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
  if(logicalIndex != Joint::TimeLineColumn)
  {
    QHeaderView::paintSection(painter, rect, logicalIndex);
    return;
  }

  // Compute the frames that should be painted
  int left = -rect.left();
  int right = left + viewport()->size().width();

  int frameFrom = left/8 -1;
  int frameTo = right/8 +1;

  // Draw background
  painter->save();
  QStyleOptionHeader option;
  initStyleOption(&option);
  option.rect = rect;
  style()->drawControl(QStyle::CE_HeaderSection, &option, painter);
  painter->restore();

  // Move the painter origin
  painter->translate(rect.left()-1, 0);

  // Draw grid
  painter->save();
  painter->setPen(QPen(Qt::lightGray));
  for(int i = frameFrom; i <= frameTo; ++i)
  {
    int x = i*8;
    painter->drawLine(x, rect.height()-4,
                      x, rect.height()-2);
    painter->drawLine(x, 0, x, 2);
  }
  painter->restore();

  // Red square (time marker)
  painter->setBrush(QColor(250, 160, 170));
  painter->setPen(QColor(200, 90, 90));
  painter->drawRect(QRect(m_currentFrame*8, 0, 8, rect.height()-2));

  // Draw first frame number (1)
  painter->setPen(QPen());
  painter->drawText(QRect(0, 0, 9, rect.height()),
                    Qt::AlignCenter, QString::number(1));

  // Draw the other frame numbers
  QRect frameRect;
  frameRect.setHeight(rect.height());
  frameRect.setWidth(8*5);
  for(int i = qMax(5, 5*(frameFrom/5)); i <= 5*(frameTo/5); i+=5)
  {
    frameRect.moveCenter(QPoint((i-1)*8+4, rect.height()/2));
    painter->drawText(frameRect, Qt::AlignCenter, QString::number(i));
  }
}

void TimeLineHeader::mousePressEvent(QMouseEvent *e)
{
  QHeaderView::mousePressEvent(e);
  if(e->buttons() & Qt::LeftButton)
    updateCurrentFrame(e->pos());
}

void TimeLineHeader::mouseMoveEvent(QMouseEvent *e)
{
  QHeaderView::mouseMoveEvent(e);
  if(e->buttons() & Qt::LeftButton)
    updateCurrentFrame(e->pos());
}

void TimeLineHeader::updateCurrentFrame(const QPoint &pos)
{
  if(logicalIndexAt(pos) != Joint::TimeLineColumn)
    return;

//  m_currentFrame = (0.5 + pos.x() + offset() - sectionPosition(s_index))/8;

//  viewport()->repaint();

  setCurrentFrame((0.5 + pos.x() + offset() - sectionPosition(Joint::TimeLineColumn))/8);
  emit currentFrameChanged(m_currentFrame);
}
