#include "timelinedelegate.h"
#include <timeline/timelineeditor.h>
#include <QDebug>
#include <animation/animation.h>

static const int HEADER_HEIGHT = 20;

TimeLineDelegate::TimeLineDelegate(QObject *parent) :
  QStyledItemDelegate(parent),
  m_currentFrame(0)
{
}

QWidget *TimeLineDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
  if(qVariantCanConvert<Animation*>(index.data()))
  {
    TimeLineEditor *editor = new TimeLineEditor(parent);
    connect(editor, SIGNAL(currentFrameChanged(int)), this, SIGNAL(currentFrameChanged(int)));
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

void TimeLineDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if(qVariantCanConvert<Animation*>(index.data()))
  {
    // ALERT - It is important to keep this function as is is, even if it does nothing.
    // It overrides the default behavior, and we want to keep the model data unchanged.
  }
  else
    QStyledItemDelegate::setModelData(editor, model, index);
}

QSize TimeLineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QSize size = QStyledItemDelegate::sizeHint(option, index);
  return QSize(size.width(), HEADER_HEIGHT);
}

void TimeLineDelegate::setCurrentFrame(int frame)
{
  if(m_currentFrame != frame)
  {
    m_currentFrame = frame;
    emit currentFrameChanged(frame);
  }
}
