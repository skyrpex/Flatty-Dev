#ifndef JOINT_H
#define JOINT_H

#include <QTreeWidgetItem>
#include <QList>
#include <joint/jointgraphicsitem.h>
#include <joint/jointtreeitem.h>

class Joint : public QObject, public JointGraphicsItem, public JointTreeItem
{
  Q_OBJECT
public:
  explicit Joint(Joint *parent = 0);

  Joint *parentJoint() const;
  QList<Joint*> childJoints() const;

public slots:
  void createAnimation();
  void removeAnimation(int i);
  void setAnimation(int i);
  void setAnimationLength(int i);
  void setFrame(int i);

private:
  QList<Animation*> m_animations;
  Animation *m_pose;
};

//Q_DECLARE_METATYPE(Joint*)

#endif // JOINT_H
