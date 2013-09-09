#ifndef QTKALMANFILTERERMENUDIALOG_H
#define QTKALMANFILTERERMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtKalmanFiltererMenuDialog;
}

namespace ribi {
namespace kalman {

class QtKalmanFiltererMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtKalmanFiltererMenuDialog(QWidget *parent = 0);
  ~QtKalmanFiltererMenuDialog();

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtKalmanFiltererMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // QTKALMANFILTERERMENUDIALOG_H
