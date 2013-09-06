#ifndef QTKALMANFILTERERMENUDIALOG_H
#define QTKALMANFILTERERMENUDIALOG_H

#include "qthideandshowdialog.h"

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC

namespace Ui {
  class QtKalmanFiltererMenuDialog;
}

namespace ribi {

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

} //~namespace ribi

#endif // QTKALMANFILTERERMENUDIALOG_H
