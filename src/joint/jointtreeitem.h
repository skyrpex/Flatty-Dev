#ifndef JOINTTREEITEM_H
#define JOINTTREEITEM_H

#include <QTreeWidgetItem>
#include <animation/animation.h>

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

  void setCurrentAnimation(Animation *currentAnimation);
  Animation *currentAnimation() const;
};

#endif // JOINTTREEITEM_H
