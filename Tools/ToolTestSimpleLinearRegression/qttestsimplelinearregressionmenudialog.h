#ifndef QTTOOLTESTSIMPLELINEARREGRESSIONMENUDIALOG_H
#define QTTOOLTESTSIMPLELINEARREGRESSIONMENUDIALOG_H

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
  explicit QtToolTestSimpleLinearRegressionMenuDialog(QWidget *parent = 0) noexcept;
  QtToolTestSimpleLinearRegressionMenuDialog(const QtToolTestSimpleLinearRegressionMenuDialog&) = delete;
  QtToolTestSimpleLinearRegressionMenuDialog& operator=(const QtToolTestSimpleLinearRegressionMenuDialog&) = delete;
  ~QtToolTestSimpleLinearRegressionMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtToolTestSimpleLinearRegressionMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLTESTSIMPLELINEARREGRESSIONMENUDIALOG_H
