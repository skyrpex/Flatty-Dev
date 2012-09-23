#include "timelinewidget.h"
#include "ui_timelinewidget.h"
#include <QScrollBar>
#include <QInputDialog>

static const char* FramesButtonTextSingular = "1 frame";
static const char* FramesButtonText = "%1 frames";
static const char* FpsButtonText = "%1 fps";

TimeLineWidget::TimeLineWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TimeLineWidget),
  m_header(new TimeLineHeader),
  m_delegate(new TimeLineDelegate),
  m_root(NULL)
{
  ui->setupUi(this);

  // Set stretch factors
  ui->splitter->setStretchFactor(ui->splitter->indexOf(ui->treeWidget), 8);

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


  connect(m_header, SIGNAL(currentFrameChanged(int)),
          m_delegate, SLOT(setCurrentFrame(int)));
  connect(m_delegate, SIGNAL(currentFrameChanged(int)),
          m_header, SLOT(setCurrentFrame(int)));


  // Adding the root joint
//  m_root = new Joint;
//  m_root->setName("Root");
//  ui->treeWidget->addTopLevelItem(m_root);

  // Adding text joints
//  Joint *joint = m_root;
//  for(int i = 0; i < 5; ++i)
//  {
//    joint = new Joint(joint);
//    joint->setName(tr("Testing long names with Qt/C++/QtCreator/Qx/Qwt/Www %1").arg(i));
//  }
}

TimeLineWidget::~TimeLineWidget()
{
  delete ui;
}

QAbstractItemModel *TimeLineWidget::model() const
{
  return ui->treeWidget->model();
}

void TimeLineWidget::setRootJoint(Joint *joint)
{
  Q_ASSERT(joint);

  m_root = joint;

  ui->treeWidget->addTopLevelItem(m_root);


  connect(m_header, SIGNAL(currentFrameChanged(int)),
          m_root, SLOT(setCurrentFrame(int)));
}

int TimeLineWidget::currentAnimation() const
{
  return ui->comboBox->currentIndex();
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

  // Make sure the header time marker is also reseted
  m_header->setCurrentFrame(0);
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
  setUiEnabled(true);
}

void TimeLineWidget::on_comboBox_currentIndexChanged(int index)
{
  // Set the current animation
  m_root->setCurrentAnimation(index);

  // Update the UI
  Animation *ani = m_root->currentAnimation();
  if(ani)
  {
    updateFramesButtonText(ani->length());
    updateFpsButtonText(ani->fps());
    ui->loopCheckBox->setChecked(ani->isLoop());
  }

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
  setUiEnabled(ui->comboBox->count());
}

void TimeLineWidget::on_framesButton_clicked()
{
  // Get the animation length from the user
  bool ok;
  int value = 60;
  int frames = QInputDialog::getInteger(this,
                                        tr("Animation length"),
                                        tr("Frames"),
                                        value, 1, 9999, 1, &ok);
  if(!ok || frames == m_root->currentAnimation()->length())
    return;

  // Update button text
  updateFramesButtonText(frames);

  // Set the animation length
  m_root->setCurrentAnimationLength(frames);

  // Update the editors (to resize the header)
  updateEditors();
}

void TimeLineWidget::on_fpsButton_clicked()
{
  // Get the animation length from the user
  bool ok;
  int value = 60;
  int fps = QInputDialog::getInteger(this,
                                     tr("Animation speed"),
                                     tr("Frames per second"),
                                     value, 1, 9999, 1, &ok);
  if(!ok || fps == m_root->currentAnimation()->fps())
    return;

  // Update button text
  updateFpsButtonText(fps);

  // Set the animation length
  m_root->setCurrentAnimationFps(fps);
}

void TimeLineWidget::on_loopCheckBox_clicked(bool checked)
{
  m_root->setCurrentAnimationIsLoop(checked);
}

void TimeLineWidget::setUiEnabled(bool enable)
{
  ui->splitter->setEnabled(enable);
  ui->comboBox->setEnabled(enable);
  ui->removeButton->setEnabled(enable);

  ui->framesButton->setEnabled(enable);
  ui->fpsButton->setEnabled(enable);
  ui->loopCheckBox->setEnabled(enable);
}

void TimeLineWidget::updateFramesButtonText(int frames)
{
  const char *text = (frames == 1)?
        FramesButtonTextSingular
      : FramesButtonText;
  ui->framesButton->setText(tr(text).arg(frames));
}

void TimeLineWidget::updateFpsButtonText(int fps)
{
  ui->fpsButton->setText(tr(FpsButtonText).arg(fps));
}
