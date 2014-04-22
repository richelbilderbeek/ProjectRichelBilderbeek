#ifndef QTTOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
#define QTTOOLTESTMULTIAPPROXIMATORMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolTestMultiApproximatorMenuDialog;
}

namespace ribi {

class QtToolTestMultiApproximatorMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolTestMultiApproximatorMenuDialog(QWidget *parent = 0) noexcept;
  QtToolTestMultiApproximatorMenuDialog(const QtToolTestMultiApproximatorMenuDialog&) = delete;
  QtToolTestMultiApproximatorMenuDialog& operator=(const QtToolTestMultiApproximatorMenuDialog&) = delete;
  ~QtToolTestMultiApproximatorMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtToolTestMultiApproximatorMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
