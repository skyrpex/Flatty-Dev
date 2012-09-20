#include "timelinewidget.h"
#include "ui_timelinewidget.h"
#include <QScrollBar>
#include <QInputDialog>

TimeLineWidget::TimeLineWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TimeLineWidget),
  m_header(new TimeLineHeader),
  m_delegate(new TimeLineDelegate),
  m_root(NULL)
{
  ui->setupUi(this);

  // Set stretch factors
  ui->splitter->setStretchFactor(ui->splitter->indexOf(ui->treeView), 1);
  ui->splitter->setStretchFactor(ui->splitter->indexOf(ui->treeWidget), 6);

  // Setup tree widget (timeline)
  ui->treeWidget->setItemDelegate(m_delegate);

  ui->treeWidget->setHeaderLabels(QStringList() << "Name" << "Timeline");
  ui->treeWidget->setHeader(m_header);
  ui->treeWidget->hideColumn(JointTreeItem::NameColumn);

  ui->treeWidget->setItemsExpandable(false);
  ui->treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  ui->treeWidget->setUniformRowHeights(true);

  ui->treeWidget->setAutoScroll(false);

  // Setup tree view (name)
  ui->treeView->setItemDelegate(m_delegate);

  ui->treeView->setModel(ui->treeWidget->model());
  ui->treeView->setSelectionModel(ui->treeWidget->selectionModel());
  ui->treeView->hideColumn(JointTreeItem::TimeLineColumn);

  ui->treeView->header()->setResizeMode(QHeaderView::ResizeToContents);
  ui->treeView->header()->setStretchLastSection(false);

  ui->treeView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  ui->treeView->setUniformRowHeights(true);

  ui->treeView->setAutoScroll(false);

  // Sync expand/collapse
  connect(ui->treeView, SIGNAL(expanded(QModelIndex)),
          ui->treeWidget, SLOT(expand(QModelIndex)));
  connect(ui->treeView, SIGNAL(collapsed(QModelIndex)),
          ui->treeWidget, SLOT(collapse(QModelIndex)));

  // Sync scrollbars
  connect(ui->treeWidget->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui->treeView->verticalScrollBar(), SLOT(setValue(int)));
  connect(ui->treeView->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui->treeWidget->verticalScrollBar(), SLOT(setValue(int)));


  connect(m_header, SIGNAL(currentFrameChangedByUser(int)),
          m_delegate, SIGNAL(currentFrameChangedByUser(int)));
  connect(m_delegate, SIGNAL(currentFrameChangedByUser(int)),
          m_header, SLOT(setCurrentFrame(int)));


  // Adding the root joint
  m_root = new Joint;
  m_root->setName("Root");
  ui->treeWidget->addTopLevelItem(m_root);

  // Adding text joints
  Joint *joint = m_root;
  for(int i = 0; i < 5; ++i)
  {
    joint = new Joint(joint);
    joint->setName(tr("Testing long names with Qt/C++/QtCreator/Qx/Qwt/Www %1").arg(i));
  }
}

TimeLineWidget::~TimeLineWidget()
{
  delete ui;
}

QAbstractItemModel *TimeLineWidget::model() const
{
  return ui->treeWidget->model();
}

void TimeLineWidget::openEditor(Joint *joint)
{
  ui->treeWidget->openPersistentEditor(joint, JointTreeItem::TimeLineColumn);
  foreach(Joint *child, joint->childJoints())
    openEditor(child);
}

void TimeLineWidget::closeEditor(Joint *joint)
{
  ui->treeWidget->closePersistentEditor(joint, JointTreeItem::TimeLineColumn);
  foreach(Joint *child, joint->childJoints())
    closeEditor(child);
}

void TimeLineWidget::updateEditors()
{
  // To correctly update the header view, we must close the editors...
  closeEditor(m_root);
  // Open them again...
  openEditor(m_root);
  m_delegate->setCurrentFrame(m_header->currentFrame());
  // And finally, expand the root item once
  bool expanded = m_root->isExpanded();
  m_root->setExpanded(!expanded);
  m_root->setExpanded(expanded);
}

void TimeLineWidget::on_addButton_clicked()
{
  QString name = QInputDialog::getText(this,
                                       tr("Create animation"),
                                       tr("Animation name"));
  if(name.isEmpty())
    return;

  // Create the animation first
  m_root->createAnimation();

  // Then, add the item and select it
  ui->comboBox->addItem(name);
  ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);

  // Enable the UI
  ui->splitter->setEnabled(true);
  ui->comboBox->setEnabled(true);
  ui->removeButton->setEnabled(true);
  ui->framesButton->setEnabled(true);
}

void TimeLineWidget::on_comboBox_currentIndexChanged(int index)
{
  // Set the current animation
  m_root->setAnimation(index);

  // Update the editors (to resize the header)
  updateEditors();
}

void TimeLineWidget::on_framesButton_clicked()
{
  // Get the animation length from the user
  bool ok;
  int value = 60;
  int length = QInputDialog::getInteger(this,
                                        tr("Animation length"),
                                        tr("Frames"),
                                        value, 1, 9999, 1, &ok);
  if(!ok)
    return;

  // Set the animation length
  m_root->setAnimationLength(length);

  // Update the editors (to resize the header)
  updateEditors();
}

void TimeLineWidget::on_removeButton_clicked()
{
  int index = ui->comboBox->currentIndex();

  // Delete the animation
  m_root->removeAnimation(index);

  // Remove the item from the ui (it also makes the skeleton to select another animation)
  ui->comboBox->removeItem(index);

  // Disable the UI if no more animations left
  ui->splitter->setEnabled(ui->comboBox->count());
  ui->comboBox->setEnabled(ui->comboBox->count());
  ui->removeButton->setEnabled(ui->comboBox->count());
  ui->framesButton->setEnabled(ui->comboBox->count());
}
