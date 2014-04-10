#ifndef QTTOOLMULTIENCRANGERMENUDIALOG_H
#define QTTOOLMULTIENCRANGERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolMultiEncrangerMenuDialog;
}

namespace ribi {

class QtMultiEncrangerMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMultiEncrangerMenuDialog(QWidget *parent = 0) noexcept;
  QtMultiEncrangerMenuDialog(const QtMultiEncrangerMenuDialog&) = delete;
  QtMultiEncrangerMenuDialog& operator=(const QtMultiEncrangerMenuDialog&) = delete;
  ~QtMultiEncrangerMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtToolMultiEncrangerMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLMULTIENCRANGERMENUDIALOG_H
