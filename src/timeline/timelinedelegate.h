#ifndef KEYFRAMEDELEGATE_H
#define KEYFRAMEDELEGATE_H

#include <QStyledItemDelegate>

class TimeLineDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  explicit TimeLineDelegate(QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:
  void setCurrentFrame(int frame);

signals:
  void currentFrameChangedByUser(int frame);
};

#endif // KEYFRAMEDELEGATE_H
