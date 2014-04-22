#ifndef QTTOOLTESTAPPROXIMATORMENUDIALOG_H
#define QTTOOLTESTAPPROXIMATORMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolTestApproximatorMenuDialog;
}

namespace ribi {

class QtToolTestApproximatorMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolTestApproximatorMenuDialog(QWidget *parent = 0) noexcept;
  QtToolTestApproximatorMenuDialog(const QtToolTestApproximatorMenuDialog&) = delete;
  QtToolTestApproximatorMenuDialog& operator=(const QtToolTestApproximatorMenuDialog&) = delete;
  ~QtToolTestApproximatorMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtToolTestApproximatorMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_xy_clicked() noexcept;
  void on_button_start_xyz_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLTESTAPPROXIMATORMENUDIALOG_H
