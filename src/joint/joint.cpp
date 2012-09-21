#include "joint.h"
#include <QDebug>

Joint::Joint(Joint *parent) :
  JointTreeItem(parent),
  m_pose(new Animation(this))
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

void Joint::setCurrentAnimation(int i)
{
  if(i != -1)
    JointTreeItem::setCurrentAnimation(m_animations.at(i));
  else
    JointTreeItem::setCurrentAnimation(NULL);
  setCurrentFrame(0);

  foreach(Joint *child, childJoints())
    child->setCurrentAnimation(i);
}

void Joint::setCurrentFrame(int i)
{
  Animation *anim = currentAnimation();
  if(anim)
  {
    KeyFrame *frameData = anim->value(i, NULL);
    if(frameData)
      setCurrentKeyFrame(frameData);
    else
      setCurrentDisplayKeyFrame(anim->displayFrameData(i));
  }
  else
    setCurrentKeyFrame(NULL);

  foreach(Joint *child, childJoints())
    child->setCurrentFrame(i);
}

void Joint::setPoseMode()
{
  qDebug() << __FUNCTION__;
  JointTreeItem::setCurrentAnimation(m_pose);
  setCurrentFrame(0);
}

void Joint::setCurrentAnimationLength(int i)
{
  Animation *anim = currentAnimation();
  if(anim)
    anim->setLength(i);

  foreach(Joint *child, childJoints())
    child->setCurrentAnimationLength(i);
}

void Joint::createAnimation()
{
  m_animations << new Animation(this);
  foreach(Joint *child, childJoints())
    child->createAnimation();
}

void Joint::removeAnimation(int i)
{
  delete m_animations.takeAt(i);
  foreach(Joint *child, childJoints())
    child->removeAnimation(i);
}
