#ifndef PONGDIALOG_H
#define PONGDIALOG_H

#include <QDialog>

namespace Ui {
class PongDialog;
}

class PongDialog : public QDialog
{
  Q_OBJECT

public:
  explicit PongDialog(QWidget *parent = 0);
  ~PongDialog();
protected:
  void keyPressEvent(QKeyEvent *);
  void timerEvent(QTimerEvent *);
private:
  Ui::PongDialog *ui;
};

#endif // PONGDIALOG_H
