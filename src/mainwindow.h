#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTreeWidget>
#include <joint/joint.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
//  QTreeWidget *m_tree;
  Joint *m_rootJoint;
};

#endif // MAINWINDOW_H
