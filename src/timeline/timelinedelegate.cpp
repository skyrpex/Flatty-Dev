#include "timelinedelegate.h"
#include <timeline/timelineeditor.h>
#include <QDebug>
#include <joint/animation.h>

static const int HEADER_HEIGHT = 20;

TimeLineDelegate::TimeLineDelegate(QObject *parent) :
  QStyledItemDelegate(parent)
{
}

QWidget *TimeLineDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
  if(qVariantCanConvert<Animation*>(index.data()))
  {
    TimeLineEditor *editor = new TimeLineEditor(parent);
    connect(editor, SIGNAL(currentFrameChangedByUser(int)), this, SIGNAL(currentFrameChangedByUser(int)));
    connect(this, SIGNAL(currentFrameChangedByUser(int)), this, SIGNAL(currentFrameChanged(int)));
    connect(this, SIGNAL(currentFrameChanged(int)), editor, SLOT(setCurrentFrame(int)));
    return editor;
  }

  return QStyledItemDelegate::createEditor(parent, option, index);
}

void TimeLineDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if(qVariantCanConvert<Animation*>(index.data()))
  {
    Animation *animation = qVariantValue<Animation*>(index.data());
    TimeLineEditor *timeLineEditor = dynamic_cast<TimeLineEditor*>(editor);
    timeLineEditor->setAnimation(animation);
  }
  else
    QStyledItemDelegate::setEditorData(editor, index);
}

QSize TimeLineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QSize size = QStyledItemDelegate::sizeHint(option, index);
  return QSize(size.width(), HEADER_HEIGHT);
}

void TimeLineDelegate::setCurrentFrame(int frame)
{
  emit currentFrameChanged(frame);
}
