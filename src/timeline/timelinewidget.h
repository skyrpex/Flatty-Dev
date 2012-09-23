#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>
#include <joint/joint.h>
#include <timeline/timelineheader.h>
#include <timeline/timelinedelegate.h>
#include <QTimer>

namespace Ui {
class TimeLineWidget;
}

class TimeLineWidget : public QWidget
{
  Q_OBJECT

public:
  explicit TimeLineWidget(QWidget *parent = 0);
  ~TimeLineWidget();

  QAbstractItemModel *model() const;

  void setRootJoint(Joint *joint);

  int currentAnimation() const;

public slots:
  void openEditor(Joint *joint);
  void closeEditor(Joint *joint);
  void updateEditors();

signals:
  void currentFrameChanged(int frame);

private slots:
  void advanceFrame();

  void on_addButton_clicked();
  void on_comboBox_currentIndexChanged(int index);
  void on_removeButton_clicked();

  void on_framesButton_clicked();
  void on_fpsButton_clicked();
  void on_loopCheckBox_clicked(bool checked);

  void on_playButton_clicked();

  void on_stopButton_clicked();

private:
  void setUiEnabled(bool enable);
  void updateFramesButtonText(int frames);
  void updateFpsButtonText(int fps);

  Ui::TimeLineWidget *ui;
  TimeLineHeader *m_header;
  TimeLineDelegate *m_delegate;
  Joint *m_root;
  QTimer m_timer;
  int m_currentTime;
};

#endif // TIMELINEWIDGET_H
