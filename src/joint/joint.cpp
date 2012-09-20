#include "joint.h"
#include <QDebug>

Joint::Joint(Joint *parent) :
  JointTreeItem(parent),
  m_pose(new Animation)
{
//  setText(0, QStrin);
//  setData(NameColumn, Qt::DisplayRole, QString("Root"));
//  QVariant variant = QVariant::fromValue<Joint*>(this);
  //  setData(TimeLineColumn, Qt::DisplayRole, variant);

//  JointTreeItem::setAnimation(m_pose);
}

Joint *Joint::parentJoint() const
{
  return dynamic_cast<Joint*>(JointTreeItem::parentItem());
}

QList<Joint *> Joint::childJoints() const
{
  QList<Joint *> children;
  foreach(JointTreeItem *item, JointTreeItem::childItems())
  {
    Joint *joint = dynamic_cast<Joint*>(item);
    if(joint)
      children << joint;
  }
  return children;
}

void Joint::setAnimation(int i)
{
  if(i != -1)
  {
    JointTreeItem::setAnimation(m_animations.at(i));
    setFrame(0);
  }
  else
    JointTreeItem::setAnimation(NULL);

  foreach(Joint *child, childJoints())
    child->setAnimation(i);
}

void Joint::setFrame(int i)
{
  qDebug() << "Joint" << __FUNCTION__ << i;
  FrameData *frameData = animation()->value(i, NULL);
//  if(frameData)
//    setFrameData(frameData);
//  else
//    setDisplayFrameData(animation()->displayFrameData(i));

  foreach(Joint *child, childJoints())
    child->setFrame(i);
}

void Joint::setAnimationLength(int i)
{
  Animation *anim = animation();
  if(anim)
    anim->setLength(i);

  foreach(Joint *child, childJoints())
    child->setAnimationLength(i);
}

void Joint::createAnimation()
{
  m_animations << new Animation;
  foreach(Joint *child, childJoints())
    child->createAnimation();
}

void Joint::removeAnimation(int i)
{
  delete m_animations.takeAt(i);
  foreach(Joint *child, childJoints())
    child->removeAnimation(i);
}
