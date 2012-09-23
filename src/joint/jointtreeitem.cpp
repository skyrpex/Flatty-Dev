#include "jointtreeitem.h"
#include <QDebug>

JointTreeItem::JointTreeItem(JointTreeItem *parent)
  : QTreeWidgetItem(parent)
{
  setFlags(flags() | Qt::ItemIsEditable);
  setCurrentAnimation(NULL);
//  setAnimation(new Animation);
}

void JointTreeItem::setName(const QString &name)
{
  setText(NameColumn, name);
}

QString JointTreeItem::name() const
{
  return text(NameColumn);
}

JointTreeItem *JointTreeItem::parentItem() const
{
  return dynamic_cast<JointTreeItem*>(parent());
}

QList<JointTreeItem *> JointTreeItem::childItems() const
{
  QList<JointTreeItem *> children;
  for(int i = 0; i < childCount(); ++i)
  {
    JointTreeItem *item = dynamic_cast<JointTreeItem*>(child(i));
    if(item)
      children << item;
  }
  return children;
}

void JointTreeItem::setCurrentAnimation(Animation *animation)
{
  setData(TimeLineColumn, Qt::DisplayRole,
          QVariant::fromValue<Animation*>(animation));
}

Animation *JointTreeItem::currentAnimation() const
{
  return qVariantValue<Animation*>(data(TimeLineColumn, Qt::DisplayRole));
}
