#ifndef JOINTTREEITEM_H
#define JOINTTREEITEM_H

#include <QTreeWidgetItem>
#include <joint/animation.h>

class JointTreeItem : public QTreeWidgetItem
{
public:
  enum Column
  {
    NameColumn = 0,
    TimeLineColumn
  };

  JointTreeItem(JointTreeItem *parent = 0);

  void setName(const QString &name);
  QString name() const;

  JointTreeItem *parentItem() const;
  QList<JointTreeItem*> childItems() const;

  void setAnimation(Animation *animation);
  Animation *animation() const;
};

#endif // JOINTTREEITEM_H
