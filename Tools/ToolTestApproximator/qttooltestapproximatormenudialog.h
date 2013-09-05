#ifndef QTTOOLTESTAPPROXIMATORMENUDIALOG_H
#define QTTOOLTESTAPPROXIMATORMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtToolTestApproximatorMenuDialog;
}

namespace ribi {

class QtToolTestApproximatorMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolTestApproximatorMenuDialog(QWidget *parent = 0);
  ~QtToolTestApproximatorMenuDialog();

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtToolTestApproximatorMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_xy_clicked();
  void on_button_start_xyz_clicked();

  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace ribi

#endif // QTTOOLTESTAPPROXIMATORMENUDIALOG_H
