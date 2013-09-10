#ifndef QTTOOLTESTAPPROXIMATORMENUDIALOG_H
#define QTTOOLTESTAPPROXIMATORMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolTestSimpleLinearRegressionMenuDialog;
}

namespace ribi {

class QtToolTestSimpleLinearRegressionMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolTestSimpleLinearRegressionMenuDialog(QWidget *parent = 0);
  ~QtToolTestSimpleLinearRegressionMenuDialog();

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtToolTestSimpleLinearRegressionMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace ribi

#endif // QTTOOLTESTAPPROXIMATORMENUDIALOG_H
