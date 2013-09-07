#ifndef QTSEARCHANDDESTROYCHESSMENUDIALOG_H
#define QTSEARCHANDDESTROYCHESSMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSearchAndDestroyChessMenuDialog;
}

namespace ribi {

class QtSearchAndDestroyChessMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtSearchAndDestroyChessMenuDialog(QWidget *parent = 0);
  ~QtSearchAndDestroyChessMenuDialog();

  static void Test();

private:
  Ui::QtSearchAndDestroyChessMenuDialog *ui;

private slots:
    void on_button_about_clicked();
    void on_button_start_clicked();
    void on_button_quit_clicked();

};

} //~namespace ribi

#endif // QTSEARCHANDDESTROYCHESSMENUDIALOG_H
