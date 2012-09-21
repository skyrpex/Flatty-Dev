#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
//  m_tree(new QTreeWidget),
  m_rootJoint(new Joint)
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
  ui->timeLineSplitter->setStretchFactor(ui->timeLineSplitter->indexOf(ui->animationListSplitter), 8);
  ui->timeLineSplitter->setStretchFactor(ui->timeLineSplitter->indexOf(ui->timeLineWidget), 1);

  ui->viewSplitter->setStretchFactor(ui->viewSplitter->indexOf(ui->modelView), 8);
  ui->meshListSplitter->setStretchFactor(ui->meshListSplitter->indexOf(ui->meshWidget), 8);

  ui->animationListSplitter->setStretchFactor(ui->animationListSplitter->indexOf(ui->animationView), 8);

  // Setup the skeleton tree
  ui->skeletonTree->setModel(ui->timeLineWidget->model());
  ui->skeletonTree->hideColumn(Joint::TimeLineColumn);
  ui->skeletonTree->header()->setResizeMode(QHeaderView::ResizeToContents);
  ui->skeletonTree->header()->setStretchLastSection(false);

  // Setup the view scenes
  ui->animationView->setScene(new QGraphicsScene(0, 0, 800, 600));
  ui->animationView->setRenderHint(QPainter::Antialiasing);
  ui->modelView->setScene(new QGraphicsScene(0, 0, 800, 600));
  ui->modelView->scene()->addPixmap(QPixmap(":/icons/mesh.png"))->setFlag(QGraphicsItem::ItemIsMovable);

  // Pass the root joint
  m_rootJoint->setName("Root");
  ui->timeLineWidget->setRootJoint(m_rootJoint);

  // Set the root joint to the default scene
//  ui->modelView->scene()->addItem(m_rootJoint);
  on_tabWidget_currentChanged(ui->tabWidget->currentWidget());
}

MainWindow::~MainWindow()
{
  delete ui;
//  delete m_tree;
}

void MainWindow::on_tabWidget_currentChanged(QWidget *arg1)
{
  if(arg1 == ui->modelTab)
  {
    m_rootJoint->setPoseMode();
    ui->modelView->scene()->addItem(m_rootJoint);
  }
  else
  {
    m_rootJoint->setCurrentAnimation(ui->timeLineWidget->currentAnimation());
    ui->animationView->scene()->addItem(m_rootJoint);
  }
}
