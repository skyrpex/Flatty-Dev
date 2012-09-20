#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)//,
//  m_tree(new QTreeWidget),
//  m_rootJoint(new Joint)
{
  ui->setupUi(this);

  // Setup the tree widget and the timeline tree
//  m_tree->setHeaderLabels(QStringList() << "Name" << "Timeline");
//  ui->timeLineWidget->setModel(m_tree->model());

//  // Setup the root joint and add to the tree
//  m_rootJoint->setName("Root");
//  m_tree->addTopLevelItem(m_rootJoint);

//  // Connect timeline widget to the root joint
//  connect(ui->timeLineWidget, SIGNAL(animationCreated()),
//          m_rootJoint, SLOT(createAnimation()));
//  connect(ui->timeLineWidget, SIGNAL(animationChanged(int)),
//          m_rootJoint, SLOT(setAnimation(int)));
//  connect(ui->timeLineWidget, SIGNAL(animationLengthChanged(int)),
//          m_rootJoint, SLOT(setAnimationLength(int)));

  // Set stretch factors
  ui->splitter->setStretchFactor(ui->splitter->indexOf(ui->timeLineWidget), 1);
  ui->splitter->setStretchFactor(ui->splitter->indexOf(ui->graphicsView), 8);


}

MainWindow::~MainWindow()
{
  delete ui;
//  delete m_tree;
}
